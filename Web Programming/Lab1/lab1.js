//Matthew Vaysfeld
//I pledge my honor that I have abided by the Stevens Honor System

const questionOne = function questionOne(arr) {
    // Implement question 1 here
    let count = 0;
    for(let i = 0; i < arr.length; i++){
        count += (arr[i] * arr[i]);
    }
    return count;
}

const questionTwo = function questionTwo(num) { 
    // Implement question 2 here
    // If the number is negative it returns 0 because "Fibonacci of anything less than 1 is 0"
    if(num < 0){
        return 0
    }
    if (num <= 1){
        return num;
    }
    return questionTwo(num-1) + questionTwo(num-2);
}

const questionThree = function questionThree(text) {
    // Implement question 3 here
    let count = 0;
    for(let i = 0; i < text.length; i++){
        if(text[i] == "a" || text[i] == "e" || text[i] == "i" || text[i] == "o" || text[i] == "u"){
            count++;
        }
    }
    return count;

}

const questionFour = function questionFour(num) {
    // Implement question 4 here
    if (num < 0){
        return NaN;
    }
    if(num == 0){
        return 1;
    }
    return num * questionFour(num-1);
}

module.exports = {
    firstName: "Matthew", 
    lastName: "Vaysfeld", 
    studentId: "10450114",
    questionOne,
    questionTwo,
    questionThree,
    questionFour
};