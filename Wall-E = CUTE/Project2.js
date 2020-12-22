// imageMapXY(img: Image, func: (img: Image, x: number, y: number) => Pixel):Image
function imageMapXY(img, f) {
  let result = img.copy();
  for (let i = 0; i < result.width; ++i) {
    for (let j = 0; j < result.height; ++j){
      let pixel = f(img, i, j);
      result.setPixel(i, j, pixel);
    }
  }
  return result;
}

let url = 'https://people.cs.umass.edu/~joydeepb/robot.jpg';
let robot = lib220.loadImageFromURL(url);
imageMapXY(robot, function(img, x, y) {
  const c = img.getPixel(x, y);
  return [c[0], 0, 0];
}).show();
robot.show();
// imageMask(img: Image,func: (img: Image, x: number, y: number) => boolean,
// maskValue: Pixel): Image
function imageMask(img, f, maskValue) {
  let result = img.copy();
  result = imageMapXY(result, function(img, x, y) {
    const c = img.getPixel(x, y);
    if (f(img, x, y) === true) {
      return maskValue;
    }
    else {
      return c;
    }
  });
  return result;
}

imageMask(robot, function(img, x, y) {
  return (y % 10 === 0);}, [1, 0, 0]).show();

// blurPixel(img: Image, x: number, y: number): Pixel
function blurPixel(img, x, y)  {
  let r = 0;
  let g = 0;
  let b = 0;
  let num = 0;
  for (let i = -1; i <= 1 ; ++i){
    for (let j = -1 ; j <= 1 ; ++j){
      // check if neighbor are not edges
      if (i+x >= 0 && i+x < img.width 
        && j+y >= 0 && j+y < img.height){
        r = r + img.getPixel(i+x, j+y)[0];
        g = g + img.getPixel(i+x, j+y)[1];
        b = b + img.getPixel(i+x, j+y)[2];
        num = num + 1;
      }
    }
  }
  return [r/num, g/num, b/num];
}

// blurImage(img: Image): Image
function blurImage(img) {
  let result = img.copy();
  result = imageMapXY(result, function(img, x, y) {
    const c = img.getPixel(x, y);
    return blurPixel(img, x, y)
  });
  result.show();
  return result;
}
blurImage(robot);

// isGrayish(p: Pixel): boolean
function isGrayish(p) {
  let r = false;
  let g = false;
  let b = false;
  if (p[0] >= 0.3 && p[0] <= 0.7) {
    r = true;
  }
  if (p[1] >= 0.3 && p[1] <= 0.7) {
    g = true;
  }
  if (p[2] >= 0.3 && p[2] <= 0.7) {
    b = true;
  }
  if (r && g && b)  {
    return true;
  }
  return false;
}
// toGrayscale(img: Image): Image
function toGrayscale(img) {

  let result = img.copy();
  result = imageMapXY(result, function(img, x, y) {
    const c = img.getPixel(x, y);
    let avg = c[0] + c[1] + c[2];
    avg = avg / 3;
    if (isGrayish(c) === true) {
      return [avg,avg,avg];
    }
    else {
      return c;
    }
  });
  return result;

}
toGrayscale(robot).show();

// saturateHigh(img: Image): Image
function saturateHigh(img)  {
  let result = img.copy();
  result = imageMapXY(result, function(img, x, y) {
    const c = img.getPixel(x, y);
    if (c[0] > 0.7){
      c[0] = 1.0;
    }
    if (c[1] > 0.7){
      c[1] = 1.0;
    }
    if (c[2] > 0.7){
      c[2] = 1.0;
    }
    return c;
  });
  return result;
}
saturateHigh(robot).show();

// blackenLow(img: Image): Image
function blackenLow(img) {
  let result = img.copy();
  result = imageMapXY(result, function(img, x, y) {
    const c = img.getPixel(x, y);
    if (c[0] < 0.3){
      c[0] = 0.0;
    }
    if (c[1] < 0.3){
      c[1] = 0.0;
    }
    if (c[2] < 0.3){
      c[2] = 0.0;
    }
    return c;
  });
  return result;
}
blackenLow(robot).show();

//reduceFunctions(fa: ((p: Pixel) => Pixel)[] ): ((x: Pixel) => Pixel)
function reduceFunctions(fa) {
  // modify(pixel: Pixel) : Pixel
  function modify(pixel)  {
    return fa.reduce((f, fofa) => fofa(f), pixel);
  }
  return modify;
}

// imageMap(img: Image, func: (p: Pixel) => Pixel): Image
function imageMap(img, func) {
  let result = img.copy();
  for (let i = 0; i < result.width; ++i) {
    for (let j = 0; j < result.height; ++j){
      let pixel = result.getPixel(i,j);
      result.setPixel(i, j, func(pixel))
    }
  }
  result.show();
  return result;
}

// colorize(img: Image): Image
function colorize(img)  {
  // create a array of function that take pixel and return pixal
  let f = [
  // modified togray function so it return pixel instead of image
  // Grayscale(c: Pixel): Pixel
  function Grayscale(c) {
    let avg = c[0] + c[1] + c[2];
    avg = avg / 3;
    if (isGrayish(c) === true) {
      return [avg,avg,avg];
    }
    else {
      return c;
    }
  }
  ,
  // modified saturate function so it return pixel instead of image
  // saturate(c: Pixel): Pixel
  function saturate(c)  {
    if (c[0] > 0.7){
      c[0] = 1.0;
    }
    if (c[1] > 0.7){
      c[1] = 1.0;
    }
    if (c[2] > 0.7){
      c[2] = 1.0;
    }
    return c;
  }
  ,
  // modified blacken function so it return pixel instead of image
    // blacken(c: Pixel): Pixel
  function blacken(c) {
    if (c[0] < 0.3){
      c[0] = 0.0;
    }
    if (c[1] < 0.3){
      c[1] = 0.0;
    }
    if (c[2] < 0.3){
      c[2] = 0.0;
    }
    return c;
  }
  ];
  return imageMap(img, reduceFunctions(f));
}
colorize(robot);

test('imageMapXY function definition is correct', function() {
let identityFunction = function(image, x, y) {
return image.getPixel(x, y);
};
let inputImage = lib220.createImage(10, 10, [0, 0, 0]);
let outputImage = imageMapXY(inputImage, identityFunction);
// Output should be an image, so getPixel must work without errors.
let p = outputImage.getPixel(0, 0);
assert(p[0] === 0);
assert(p[1] === 0);
assert(p[2] === 0);
assert(inputImage !== outputImage);
});
function pixelEq (p1, p2) {
const epsilon = 0.002;
for (let i = 0; i < 3; ++i) {
if (Math.abs(p1[i] - p2[i]) > epsilon) {
return false;
}
}
return true;
};
test('identity function with imageMapXY', function() {
let identityFunction = function(image, x, y ) {
return image.getPixel(x, y);
};
let inputImage = lib220.createImage(10, 10, [0.2, 0.2, 0.2]);
inputImage.setPixel(0, 0, [0.5, 0.5, 0.5]);
inputImage.setPixel(5, 5, [0.1, 0.2, 0.3]);
inputImage.setPixel(2, 8, [0.9, 0.7, 0.8]);
let outputImage = imageMapXY(inputImage, identityFunction);
assert(pixelEq(outputImage.getPixel(0, 0), [0.5, 0.5, 0.5]));
assert(pixelEq(outputImage.getPixel(5, 5), [0.1, 0.2, 0.3]));
assert(pixelEq(outputImage.getPixel(2, 8), [0.9, 0.7, 0.8]));
assert(pixelEq(outputImage.getPixel(9, 9), [0.2, 0.2, 0.2]));
});