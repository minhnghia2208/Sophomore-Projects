// type State = { [key: string]: number | boolean }

class FSA {
  // currentState which is a State encoding the current state
  
  // arrayOfStates which stores the different states that the machine can be in, as
  // defined by successive calls to the createState() method
  constructor() {
    this.currentState = () => {};
    this.arrayOfStates = () => [];
  }
  // nextState(s: string): returns this
  nextState(s) {
    let store = [];
    if (this.arrayOfStates().length !== 0) {
      store = this.arrayOfStates().filter(function(arr) {
        return arr.name === this.currentState().nextState(s);;
      });
      this.currentState = () => store[0];
    }
    return this;
  }
 
  createState(s, transitions) {
    let store = new State();
    let store1 = this.arrayOfStates();
  
    store.name = s;
    store.transitions = transitions;

    store1.push(store);
    
    if (this.currentState() === undefined) {
      this.currentState = () => store;
    }

    this.arrayOfStates = () => store1;
    return this;
  }

  // getStateDescription(): string
  getStateDescription() {
//    let store = this.currentState();
    if (this.currentState() === undefined) {
      return "";
    }
    else {
      return this.currentState().name;
    }
  }
  // createMemento(): Memento
  createMemento() {
    let store = new Memento();
    if (this.currentState() === undefined) {
      store.storeState(undefined);
      return store;
    }
    else {
      store.storeState(this.currentState());
      return store;
    }
  }
  // restoreMemento(m: Memento): returns this
  restoreMemento(m) {
    this.currentState = () => m.getState();
    return this;
  }
}
// random
function randomInt(min, max) {
  return Math.floor(Math.random() * (max - min)) + min;
}

class State {
  // name: string.
  // transitions: Transition[]
  constructor() {
    this.name = () => "";
    this.transitions = () => [];
  }
  // setName(s: string): returns this . Stores its input argument into attribute name .
  setName(s) {
    this.name = () => s;
    return this;
  }
  // getName(): string
  getName() {
    return this.name();
  }
  // nextState(s: string): string
  nextState(s) {
    let store = [];
    store = this.transitions().filter(function(trans) {
      return lib220.getProperty(trans, s).found;
    });
    if (store.length === 0) {
      return "";
    }
    else {
      if (store.length === 1) {
      return lib220.getProperty(store[0], s).value;
      }
      else {
        return lib220.getProperty(store[randomInt(0, store.length)], s).value;
      }
    }
  }
  // addTransition(s1: string, s2: string)
  addTransition(s1, s2) {
    let store = this.transitions();
    let dict = {};
    lib220.setProperty(dict, s1, s2);
    store.push(dict);
    this.transitions = () => store;
    console.log(this.transitions());
  }
}
class Memento {
  constructor() {
    this.State = {};
  }
  // storeState(s: State)
  storeState(s) {
    this.State =  s;
    return this;
  }
  // getState(): State
  getState() {
    return State;
  }
}
/*
let a = new State()
a.setName("Name").addTransition("low","high");
console.log(a.nextState("low"));
let myMachine = new FSA().createState("delicates, low", [{"Mode button pressed":"normal, low"},{"Temp button pressed": "delicates, medium"}]);
.createState("normal, low", [{"Mode button pressed":"delicates, low"},
{"Temp button pressed": "normal, medium"}])
.createState("delicates, medium", [{"Mode button pressed":"normal, medium"},
{"Temp button pressed": "delicates, low"}])
.createState("normal, medium", [{"Mode button pressed" : "delicates, medium"},
{"Temp button pressed" : "normal, high"}])
.createState("normal, high", [{"Mode button pressed" : "delicates, medium"},
{"Temp button pressed": "normal, low"}]);

myMachine.nextState("Temp button pressed") // moves the machine to delicates, medium
.nextState("Mode button pressed") // moves the machine to normal, medium
.nextState("Temp button pressed") // moves the machine to normal, high
console.log(myMachine.getStateDescription());
*/
let mode= 'Mode button pressed'
let temp= 'Temp button pressed'
let obj11 = {}
let obj12 = {}
let obj21 = {}
let obj22 = {}
let obj31 = {}
let obj32 = {}
let obj41 = {}
let obj42 = {}
let obj51 = {}
let obj52 = {}

lib220.setProperty(obj11 , mode, 'normal, low')
lib220.setProperty(obj12 , temp, 'delicates, medium')
lib220.setProperty(obj21 , mode,'delicates, low')
lib220.setProperty(obj22 , temp, 'normal, medium')
lib220.setProperty(obj31 , mode, 'normal, medium')
lib220.setProperty(obj32 , temp, 'delicates, low')
lib220.setProperty(obj41 , mode,'normal, low')
lib220.setProperty(obj42 , temp, 'delicates, medium')
lib220.setProperty(obj51 , mode,'delicates, medium')
lib220.setProperty(obj52 , temp, 'normal, medium')

let myMachine = new FSA();
myMachine.createState('delicates, low', [obj11, obj12]);
console.log(myMachine.getStateDescription());