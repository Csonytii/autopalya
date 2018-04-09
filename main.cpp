#include <iostream>
#include <cmath>
#include <vector>
#include <list>

using namespace std;

class City {
    string name;

    int X, Y;

public:
    City();

    string getName() const;

    void setName(const string &value);

    int getX() const;

    void setX(int value);

    int getY() const;

    void setY(int value);
};


class Citiesver2 {
    int N = 0, K = 0;

    int eucledian(City *first, City *second);

    int counter = 0;
    vector<City *> cities;
    list<string> solutionlist;
    City *first;
public:

    ~Citiesver2();

    void setN(int value);

    void setK(int value);

    void addto(const string &name, int X, int Y);

    void greedy();

    void listing();
};

void Citiesver2::setN(int value) {
    N = value;

    cities.resize((unsigned long) N);
}

void Citiesver2::setK(int value) {
    K = value;
}

//simple adding
void Citiesver2::addto(const string &name, int X, int Y) {
    auto *Current = new City();
    Current->setName(name);
    Current->setX(X);
    Current->setY(Y);
    cities[counter] = Current;
    if (counter == 0)
        first = cities[0];


    counter++;
}

//Greedy algorithm
void Citiesver2::greedy() {
    City *Currentcity = first;
    vector<bool> visited;
    vector<int> distance;
    visited.resize(N);
    string cityname = Currentcity->getName();
    solutionlist.push_back(cityname);
    visited[0] = true;
    int j = 0;
    while (j < (K - 1)) {
        for (auto it: cities) {
            distance.push_back(eucledian(Currentcity, it));
        }
        int x = 0;
        int min = pow(10, 9) + 1;
        for (int i = 0; i < N; i++) {
            if (distance[i] != 0 && (distance[i] < min) && visited[i] == false) {
                min = distance[i];
                Currentcity = cities[i];
                x = i;
                cityname = Currentcity->getName();
            }
        }
        visited[x] = true;
        solutionlist.push_back(cityname);
        distance.clear();
        distance.resize(0);
        j++;
    }
    for (auto i : cities) {
        delete i;
    }
    visited.clear();
    visited.resize(0);
    cities.resize(0);
}

void Citiesver2::listing() {
    for (auto it:solutionlist) {
        cout << it << endl;
    }
}

int Citiesver2::eucledian(City *first, City *second) {
    return (pow(first->getX() - second->getX(), 2) + pow(first->getY() - second->getY(), 2));
}

string City::getName() const {
    return name;
}

void City::setName(const string &value) {
    name = value;
}

int City::getX() const {
    return X;
}

void City::setX(int value) {
    X = value;
}

int City::getY() const {
    return Y;
}

void City::setY(int value) {
    Y = value;
}

City::City() {

}


Citiesver2::~Citiesver2() {
    for (auto i : cities) {
        delete i;
    }
}


int main() {
    //input
    auto *C = new Citiesver2;
    int N = 0, K = 0;
    bool isgood;
    do {
        cerr << "N: ";
        cin >> N;
        isgood = 2 <= N && N <= 1000000;
        if (!isgood) {
            cerr << "Wrong input" << endl;

        }
    } while (!isgood);
    C->setN(N);
    do {
        cerr << "K: ";
        cin >> K;
        isgood = 2 <= K && K <= N;
        if (!isgood) {
            cerr << "Wrong input" << endl;
        }
    } while (!isgood);

    C->setK(K);
    //still input ._.
    string cityname;
    int X, Y;
    int i = 0;
    while (i < N) {
        cerr << "cityname: ";

        cin >> cityname;
        cerr << endl << cityname << " ";
        do {
            cerr << endl << "X: ";
            cin >> X;
            isgood = pow(-10, 9) <= X && X <= pow(10, 9);
            if (!isgood) {
                cerr << "Wrong input" << endl;
            }
        } while (!isgood);
        do {
            cerr << "Y: ";
            cin >> Y;
            isgood = pow(-10, 9) <= Y && Y <= pow(10, 9);
            if (!isgood) {
                cerr << "Wrong input" << endl;
            }
        } while (!isgood);
        i++;
        C->addto(cityname, X, Y);
    }
    //and now the magic
    //ellen

    C->greedy();
    C->listing();

    return 0;
}
