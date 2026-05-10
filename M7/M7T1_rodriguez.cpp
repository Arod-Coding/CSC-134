// M7T1
// Adrian Rodriguez
// 5/4/2026

#include <iostream>
using namespace std;

class Restaurant {
    private:
     string name;   // name of the place
     double rating; // 1-5 stars, including half stars

    public:
     Restaurant(string n, double r) {
        name = n;
        rating = r;
     }

    // Getters and Setters
    void setName(string n) {
        name = n;
    }
    void setRating(double r) {
        rating = r;
    }
    string getName() const {
        return name;
    }
    double getRating() const {
        return rating;
    }

    // Displays the restaurant name and its rating visually
    void display() const {
        cout << name << ": ";
        
        int fullStars = static_cast<int>(rating); 
        bool hasHalfStar = (rating - fullStars) >= 0.5;

        for (int i = 0; i < fullStars; i++) {
            cout << "⭐";
        }

        if (hasHalfStar) {
            cout << "✨";
        }

        cout << " (" << rating << "/5)" << endl;
    }
};

int main() {
    cout << "Restaurant Reviews" << endl;

    // Create three restaurant objects
    Restaurant rest1("Mi Casita", 4.0);
    Restaurant rest2("Olive Garden", 3.5);
    Restaurant rest3("Sakura Sushi", 4.5);

    // Display all restaurants
    rest1.display();
    rest2.display();
    rest3.display();

    return 0;
}