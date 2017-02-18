#include <iostream>
#include <random>
#include <iomanip>
#include <ctime>

void displayMenu() {
  std::cout
      << "\nPlease choose one of the following options for your math quiz:\n"
      << "1. Addition with numbers 1 - 10\n"
      << "2. Addition with numbers 1 - 100\n"
      << "3. Subtraction with numbers 1 - 10\n"
      << "4. Subtraction with numbers 1 - 100\n"
      << "5. Multiplication with numbers 1 - 10\n"
      << "6. Exit the program\n\n";
}

int quizEngine(int lowerBound, int upperBound, char expressionOperator) {
  int amountCorrect = 0;
  std::mt19937 rng;
  rng.seed(static_cast<unsigned int>(time(nullptr)));
  for (int i = 0; i < 5; i++) {
    std::uniform_int_distribution<std::mt19937::result_type> tRand(lowerBound, upperBound);
    int number_1 = tRand(rng);
    int number_2 = tRand(rng);
    int correctAnswer = 0;
    switch (expressionOperator) {
    case '+':
      correctAnswer = number_1 + number_2;
      break;
    case '-':
      correctAnswer = number_1 - number_2;
      break;
    case '*':
      correctAnswer = number_1 * number_2;
      break;
    }
    std::cout << "Enter the answer to the following problem: " << number_1
	      << ' ' << expressionOperator << ' ' << number_2 << ' ';
    int userAnswer = 0;
    std::cin >> userAnswer;
    if (!std::cin) {
	    std::cin.clear();
	    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	    goto incorrect;
    }
    if (userAnswer == correctAnswer) {
      amountCorrect += 1;
      std::cout << "That is the correct answer!\n\n";
    } else {
incorrect:
      std::cout << "Sorry, that is incorrect. The correct answer is "
                << correctAnswer << "\n\n";
    }
  }
  return amountCorrect;
}

int main() {
  std::cout << "Welcome to the of Math!\n\n";
  int amountCorrect = 0, problemsAttempted = 0;
  bool quit = false;
  while (!quit) {
    displayMenu();
    int choice;
    std::cin >> choice;
    if (!std::cin) {
	    std::cin.clear();
	    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	    goto input;
    }
    switch (choice) {
    case 1:
      problemsAttempted += 5;
      amountCorrect += quizEngine(1, 10, '+');
      break;
    case 2:
      problemsAttempted += 5;
      amountCorrect += quizEngine(1, 100, '+');
      break;
    case 3:
      problemsAttempted += 5;
      amountCorrect += quizEngine(1, 10, '-');
      break;
    case 4:
      problemsAttempted += 5;
      amountCorrect += quizEngine(1, 100, '-');
      break;
    case 5:
      problemsAttempted += 5;
      amountCorrect += quizEngine(1, 10, '*');
      break;
    case 6:
      quit = true;
      break;
    default:
input:
      std::cout << "Valid choices are 1-6; please re-enter.";
    }
  }
  float percentage = 0.00;
  if (problemsAttempted != 0) {
    percentage = (amountCorrect / static_cast<float>(problemsAttempted)) * 100;
  }
  std::cout << "You got " << amountCorrect << " problems correct out of "
            << problemsAttempted << " problems attempted. That is "
            << std::fixed << std::setprecision(2) << percentage << " percent correct. Goodbye!\n";
}
