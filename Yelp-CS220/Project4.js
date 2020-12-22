/*
type Restaurant = {
  name: string,
  city: string,
  state: string,
  stars: number,
  review_count: number,
  attributes: {} | {
    Ambience: {
    [key: string]: boolean
    }
  },
  categories: string[]
}
*/

/* getProperty(obj: Object, memberStr: string):
  { found: true, value: any } | { found: false }
*/

class FluentRestaurants {
  constructor(jsonData) {
    this.data = jsonData;
  }
  // fromState(stateStr: string): FluentRestaurants
  // filter<T>(f: (x : T) => boolean, a: T[]): T[]
  
  fromState(stateStr){
    let result = [];
    result = this.data.filter(function(js) {
      if (lib220.getProperty(js, 'state').found) {
        return lib220.getProperty(js, 'state').value === stateStr;
      }
      else { return false; }
    });
    return new FluentRestaurants(result);
  }

  // ratingLeq(rating: number): FluentRestaurants
  ratingLeq(rating) {
    let result = [];
    result = this.data.filter(function(js) {
      if (lib220.getProperty(js, 'stars').found) {
        return lib220.getProperty(js, 'stars').value <= rating;
      }
      else { return false; }
      });
    return new FluentRestaurants(result);
  }
  // ratingGeq(rating: number): FluentRestaurants
  ratingGeq(rating) {
    let result = [];
    result = this.data.filter(function(js) {
      if (lib220.getProperty(js, 'stars').found) {
        return lib220.getProperty(js, 'stars').value >= rating;
      }
      else { return false;}
    });
    return new FluentRestaurants(result);
  }
  // category(categoryStr: string): FluentRestaurants
  category(categoryStr) {
    let result = [];
    result = this.data.filter(function(js) {
      if (lib220.getProperty(js, 'categories').found) {
        let store = lib220.getProperty(js, 'categories').value;
        store.includes(categoryStr);
        return store.includes(categoryStr);
      }
      else { return false;}
    });
    return new FluentRestaurants(result);
  }
  // hasAmbience(ambienceStr: string): FluentRestaurants
  hasAmbience(ambienceStr)  {
    let result = [];
    result = this.data.filter(function(js) {
      if (lib220.getProperty(js, 'attributes').found) {
        let store = lib220.getProperty(js, 'attributes').value;
        if (lib220.getProperty(store, 'Ambience').found) {
          if (lib220.getProperty(lib220.getProperty(store, 'Ambience').value, ambienceStr).found) {
            return lib220.getProperty(lib220.getProperty(store, 'Ambience').value, ambienceStr).value;
          }
          else { return false; }
        }
        else { return false; }
      }
      else { return false;}
    });
    return new FluentRestaurants(result);
  }
  // bestPlace(): Restaurant | {}
  bestPlace() {

    // reduce<A, B>(a: B[], f: (A, B) => A, init: A): A
    let f = this.data.reduce(function(result, js) {
      if (lib220.getProperty(js, 'stars').found) {
        if (lib220.getProperty(result, 'stars').found) {
          if (lib220.getProperty(js, 'stars').value > lib220.getProperty(result, 'stars').value){
            return js;
          }
          if (lib220.getProperty(js, 'stars').value === lib220.getProperty(result, 'stars').value){
            if (lib220.getProperty(js, 'review_count').found) {
              if (lib220.getProperty(result, 'review_count').found) {
                if (lib220.getProperty(js, 'review_count').value <= lib220.getProperty(result, 'review_count').value){ 
                  return result;
                }
                else { return js; }
              }
              else { return js; }
            }
            else {
              return result;
            }
          }
          if (lib220.getProperty(js, 'stars').value < lib220.getProperty(result, 'stars').value){
            return result;
          }
        }
        else { return js; }
      }
      else { return result; }}, {});
      return f;
  }
  
}

let data = lib220.loadJSONFromURL('https://people.cs.umass.edu/~joydeepb/yelp.json');
let f = new FluentRestaurants(data);
console.log(f.ratingLeq(5)
.ratingGeq(3)
.category('Restaurants')
.hasAmbience('casual')
.fromState('NV')
.bestPlace().name);

const testData = [
  {
  name: "Applebee's",
  state: "NC",
  stars: 4,
  review_count: 6,
  },
  {
  name: "China Garden",
  state: "NC",
  stars: 4,
  review_count: 10,
  },
  {
  name: "Beach Ventures Roofing",
  state: "AZ",
  stars: 3,
  review_count: 30,
  },
  {
  name: "Alpaul Automobile Wash",
  state: "NC",
  stars: 3,
  review_count: 30,
  }
]
test('fromState filters correctly', function() {
  let tObj = new FluentRestaurants(testData);
  let list = tObj.fromState("NC").data;
  assert(list.length === 3);
  assert(list[0].name === "Applebee's");
  assert(list[1].name === "China Garden");
  assert(list[2].name === "Alpaul Automobile Wash");
});
test('bestPlace tie-breaking', function() {
  let tObj = new FluentRestaurants(testData);
  let place = tObj.fromState('NC').bestPlace();
  assert(place.name === 'China Garden');
});
