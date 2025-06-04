
#include <iostream>
#include <random>
#include <string>
#include <limits>
#include <iomanip>

class GuessingGame {
private:
    std::random_device rd;
    std::mt19937 gen;
    int targetNumber;
    int attempts;
    int maxAttempts;
    int score;
    int totalGames;
    int totalWins;
    std::string difficulty;
    int minRange;
    int maxRange;

public:
    GuessingGame() : gen(rd()), attempts(0), score(0), totalGames(0), totalWins(0) {}

    void displayWelcome() {
        std::cout << "\n╔══════════════════════════════════════╗\n";
        std::cout << "║        NUMBER GUESSING GAME          ║\n";
        std::cout << "║    Challenge yourself and have fun!  ║\n";
        std::cout << "╚══════════════════════════════════════╝\n\n";
    }

    void displayStats() {
        if (totalGames > 0) {
            double winRate = (static_cast<double>(totalWins) / totalGames) * 100;
            std::cout << "\n📊 GAME STATISTICS:\n";
            std::cout << "   Games Played: " << totalGames << "\n";
            std::cout << "   Games Won: " << totalWins << "\n";
            std::cout << "   Win Rate: " << std::fixed << std::setprecision(1) << winRate << "%\n";
            std::cout << "   Total Score: " << score << "\n\n";
        }
    }

    int selectDifficulty() {
        int choice;
        std::cout << "🎯 SELECT DIFFICULTY LEVEL:\n\n";
        std::cout << "1. 😊 Easy   (1-50,  8 attempts)\n";
        std::cout << "2. 😐 Medium (1-100, 7 attempts)\n";
        std::cout << "3. 😤 Hard   (1-200, 6 attempts)\n";
        std::cout << "4. 😵 Expert (1-500, 5 attempts)\n\n";
        std::cout << "5. 💀 Insane (1-1000, 4 attempts)\n\n";
        std::cout << "Enter your choice (1-5): ";

        while (!(std::cin >> choice) || choice < 1 || choice > 5) {
            std::cout << "❌ Invalid choice! Please enter 1-5: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1:
                difficulty = "Easy";
                minRange = 1;
                maxRange = 50;
                maxAttempts = 8;
                break;
            case 2:
                difficulty = "Medium";
                minRange = 1;
                maxRange = 100;
                maxAttempts = 7;
                break;
            case 3:
                difficulty = "Hard";
                minRange = 1;
                maxRange = 200;
                maxAttempts = 6;
                break;
            case 4:
                difficulty = "Expert";
                minRange = 1;
                maxRange = 500;
                maxAttempts = 5;
                break;
            case 5:
            difficulty = "Insane";
            minRange = 1;
            maxRange = 1000;
            maxAttempts = 4;
            break;
        }

        return choice;
    }

    void generateNumber() {
        std::uniform_int_distribution<> dis(minRange, maxRange);
        targetNumber = dis(gen);
        attempts = 0;
    }

    void displayGameInfo() {
        std::cout << "\n🎮 GAME STARTED!\n";
        std::cout << "Difficulty: " << difficulty << "\n";
        std::cout << "Range: " << minRange << " - " << maxRange << "\n";
        std::cout << "Max Attempts: " << maxAttempts << "\n";
        std::cout << "Current Score: " << score << "\n";
        std::cout << "═══════════════════════════════════════\n\n";
    }

    std::string getHint(int guess) {
        int difference = std::abs(guess - targetNumber);
        if (difference <= 5) return "🔥 Very Hot!";
        else if (difference <= 15) return "🌡️ Hot!";
        else if (difference <= 30) return "😐 Warm";
        else if (difference <= 50) return "❄️ Cold";
        else return "🧊 Very Cold!";
    }

    bool playRound() {
        generateNumber();
        displayGameInfo();

        while (attempts < maxAttempts) {
            int guess;
            std::cout << "Attempt " << (attempts + 1) << "/" << maxAttempts << " - Enter your guess: ";

            while (!(std::cin >> guess)) {
                std::cout << "❌ Invalid input! Please enter a number: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            attempts++;

            if (guess == targetNumber) {
                int roundScore = calculateScore();
                score += roundScore;
                totalWins++;

                std::cout << "\n🎉 CONGRATULATIONS! 🎉\n";
                std::cout << "You guessed the number " << targetNumber << " correctly!\n";
                std::cout << "Attempts used: " << attempts << "/" << maxAttempts << "\n";
                std::cout << "Round Score: +" << roundScore << " points\n";
                std::cout << "Total Score: " << score << " points\n\n";
                return true;
            }

            if (attempts < maxAttempts) {
                if (guess < targetNumber) {
                    std::cout << "📈 Too low! ";
                } else {
                    std::cout << "📉 Too high! ";
                }
                std::cout << getHint(guess) << "\n";
                std::cout << "Attempts remaining: " << (maxAttempts - attempts) << "\n\n";
            }
        }

        std::cout << "\n💔 GAME OVER!\n";
        std::cout << "The number was: " << targetNumber << "\n";
        std::cout << "Better luck next time!\n\n";
        return false;
    }

    int calculateScore() {
        int baseScore = 100;
        int difficultyMultiplier;

        switch (maxAttempts) {
            case 8: difficultyMultiplier = 1; break;  // Easy
            case 7: difficultyMultiplier = 2; break;  // Medium
            case 6: difficultyMultiplier = 3; break;  // Hard
            case 5: difficultyMultiplier = 5; break;  // Expert
            case 4: difficultyMultiplier = 6; break;  // Insane
            default: difficultyMultiplier = 1;
        }

        int attemptsBonus = (maxAttempts - attempts) * 10;
        return (baseScore + attemptsBonus) * difficultyMultiplier;
    }

    bool playAgain() {
        char choice;
        std::cout << "Would you like to play again? (y/n): ";
        std::cin >> choice;
        return (choice == 'y' || choice == 'Y');
    }

    void displayFinalStats() {
        std::cout << "\n╔══════════════════════════════════════╗\n";
        std::cout << "║           FINAL STATISTICS           ║\n";
        std::cout << "╚══════════════════════════════════════╝\n";
        
        if (totalGames > 0) {
            double winRate = (static_cast<double>(totalWins) / totalGames) * 100;
            std::cout << "Games Played: " << totalGames << "\n";
            std::cout << "Games Won: " << totalWins << "\n";
            std::cout << "Win Rate: " << std::fixed << std::setprecision(1) << winRate << "%\n";
            std::cout << "Final Score: " << score << " points\n\n";
            
            if (winRate >= 80) {
                std::cout << "🏆 Excellent performance! You're a guessing master!\n";
            } else if (winRate >= 60) {
                std::cout << "🥈 Great job! You're getting good at this!\n";
            } else if (winRate >= 40) {
                std::cout << "🥉 Not bad! Keep practicing to improve!\n";
            } else {
                std::cout << "📚 Keep trying! Practice makes perfect!\n";
            }
        }
        
        std::cout << "\nThanks for playing! 👋, Made by Richie!\n\n";
    }

    void run() {
        displayWelcome();
        
        do {
            displayStats();
            selectDifficulty();
            totalGames++;
            playRound();
        } while (playAgain());
        
        displayFinalStats();
    }
};

int main() {
    GuessingGame game;
    game.run();
    return 0;
}
