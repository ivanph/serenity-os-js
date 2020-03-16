function foo() {
  var y = 1;
  return function bar () {
    return y;
  }	
}
foo()();
