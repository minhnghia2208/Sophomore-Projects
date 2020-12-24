// type State = { [key: string]: number | boolean }

// Given a state object and an AST of an expression as arguments,
// interpExpression returns the result of the expression (number or boolean)
// interpExpression(state: State, e: Expr): number | boolean
// The State type is explained further down the document.
// Given a state object and an AST of a statement,
function interpExpression(state, e) {
  if (e.kind === 'number' || e.kind === 'boolean') {
    return e.value;
  }
  else if (e.kind === 'variable') {
    return lib220.getProperty(state, e.name).value;
  }

  else if (e.kind === 'operator') {

    if (e.op === '+') {
      return interpExpression(state, e.e1) + interpExpression(state, e.e2);
    }

    else if (e.op === '-') {
      return interpExpression(state, e.e1) - interpExpression(state, e.e2);
    }

    else if (e.op === '*') {
      return interpExpression(state, e.e1) * interpExpression(state, e.e2);
    }
    else if (e.op === '/') {
      return interpExpression(state, e.e1) / interpExpression(state, e.e2);
    }
    else if (e.op === '>') {
      return interpExpression(state, e.e1) > interpExpression(state, e.e2);
    }
    else if (e.op === '<') {
      return interpExpression(state, e.e1) < interpExpression(state, e.e2);
    }
    else if (e.op === '===') {
      return interpExpression(state, e.e1) === interpExpression(state, e.e2);
    }
    else if (e.op === '&&') {
      return interpExpression(state, e.e1) && interpExpression(state, e.e2);
    }
    else if (e.op === '||') {
      return interpExpression(state, e.e1) || interpExpression(state, e.e2);
    }
  }
  else {
    assert(false);
  }
}
// console.log(interpExpression({ x: 10 }, parser.parseExpression("x * 2").value));
test("multiplication with a variable", function() {
  let r = interpExpression({ x: 10, y:2, z:3 }, parser.parseExpression("x * y").value);
  assert(r === 20);
});
test("divide with a variable", function() {
  let r = interpExpression({ x: 10, y:2 }, parser.parseExpression("x / y").value);
  assert(r === 5);
});
test("greater with a variable", function() {
  let r = interpExpression({ x: 10, y:2 }, parser.parseExpression("x > y").value);
  assert(r);
});
test("lesser with a variable", function() {
  let r = interpExpression({ x: 10, y:2 }, parser.parseExpression("x < y").value);
  assert(!r);
});
test("&& with a variable", function() {
  let r = interpExpression({ x: true, y:false }, parser.parseExpression("x && y").value);
  assert(!r);
});
test("|| with a variable", function() {
  let r = interpExpression({ x: true, y:false }, parser.parseExpression("x || y").value);
  assert(r);
});

// interpStatement updates the state object and returns nothing
// interpStatement(state: State, p: Stmt): void
function interpStatement(state, s) {
  
  if (s.kind === 'let' || s.kind === 'assignment') {
    let value = interpExpression(state, s.expression);
    lib220.setProperty(state, s.name, value);
  }
  
  if (s.kind === 'print') {
    print(interpExpression(state, s.expression));
  }

  if (s.kind === 'if') {
    let value = interpExpression(state, s.test);
    if (value) {
      interpBlock(state, s.truePart);
    } 
    else {
      interpBlock(state, s.falsePart);
    }
  }

  if (s.kind === 'while') {
    let modifiedAST = {
      kind: 'if',
      test: s.test,
      truePart: s.body.concat(s),
      falsePart: []
    };
    interpStatement(state, modifiedAST);
  }
}
function interpBlock(state, st) {
  let store = Object.assign({}, state);
  while (st.length !== 0) {
    if (st[0].kind === 'let') {
      interpStatement(store, st[0]);
    }
    else {
      interpStatement(state, st[0]);
    }
    st.shift();
  }
}

let x = {a:1, b:10};
interpStatement(x, { kind: 'if', test: { kind: 'boolean', value: false }, 
truePart: [{ kind: 'let', name: 'c', 
expression: { kind: 'operator', op: '+', e1: {kind: "variable", name: 'a'}, e2: {kind: "number", value: 1} }}], 
falsePart: [{ kind: 'assignment', name: 'a', 
expression: { kind: 'operator', op: '+', e1: {kind: "variable", name: 'a'}, e2: {kind: "number", value: 2} }}]});
console.log(x);

// Given the AST of a program,
// interpProgram returns the final state of the program
// interpProgram(p: Stmt[]): State
function interpProgram(p) {
  let store = {};
  let state = {};
  while (p.length !== 0) {
    store = p[0];
    interpStatement(state, p[0]);
    p.shift();
  }
  return state;
}
let st = interpProgram([
    { kind: "let", name: "x", expression: { kind: "number", value: 10 } },
    { kind: "assignment", name: "x",
    expression: {
    kind: "operator", op: "*", e1: { kind: "variable", name: "x" },
    e2: { kind: "number", value: 2 } } } ]);
console.log(st);
st = interpProgram(parser.parseProgram("let x = 10; x = x * 2;").value);
console.log(st);
test("assignment", function() {
  let st = interpProgram(parser.parseProgram("let x = 10; x = 20;").value);
  assert(st.x === 20);
});