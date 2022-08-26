function isPrime(num){
    if(num <= 0){
      // can also be not prime but according to slack we need to throw an error
      throw "Enter a number greater than 0"
    }
    if(typeof(num) !== "number" || isNaN(num)){
      throw "Must enter a number"
    }
    if(!Number.isInteger(num)){
      // can also be not prime but according to slack we need to throw an error
      throw "Enter a whole number"
    }
    if(!num){
        throw "Input does not exist"
    }
    if(arguments.length != 1){
        throw "too many arguments"
    }
  //https://stackoverflow.com/questions/40200089/number-prime-test-in-javascript
  for(let i = 2, s = Math.sqrt(num); i <= s; i++)
        if(num % i === 0){
            return false; 
        } 
    return num > 1;
}


let myForm = document.getElementById('myForm');
let numberInput = document.getElementById('number');
let errorDiv = document.getElementById('error');
let attemptsList = document.getElementById('attempts');
let frmLabel = document.getElementById('formLabel');

if (myForm) {
  myForm.addEventListener('submit', (event) => {
    event.preventDefault();
    if (numberInput.value.trim()) {
      numberInput.classList.remove('inputClass');
      errorDiv.hidden = true;
      frmLabel.classList.remove('error');
      let li = document.createElement('li');
      const parsednumberInput = Number(numberInput.value);
      try{
        let val = isPrime(parsednumberInput)
        if(val){
          li.className = "is-prime";
          li.innerHTML = numberInput.value + ' is a prime number';
        }
        else{
          li.className = "not-prime";
          li.innerHTML = numberInput.value + ' is NOT a prime number';
        }
        attemptsList.appendChild(li);
        myForm.reset();
        numberInput.focus();
      }catch(e){
        errorDiv.hidden = false;
        errorDiv.innerHTML = e;
        frmLabel.className = 'error';
        numberInput.focus();
        numberInput.className = 'inputClass';
        myForm.reset();
      }
    } else {
      errorDiv.hidden = false;
      errorDiv.innerHTML = 'You must enter a value';
      frmLabel.className = 'error';
      numberInput.focus();
      numberInput.className = 'inputClass';
    }
  });
}