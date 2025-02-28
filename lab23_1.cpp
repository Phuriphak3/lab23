#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream file(filename.c_str());
    if(!file.is_open()){
        cerr << "Cannot open file: " << filename << endl;
        exit(1);
    }

    string line;
    while(getline(file, line)){
        size_t colonPos = line.find(":");
        string name = line.substr(0, colonPos);
        string scoreStr = line.substr(colonPos + 1);

        int score1, score2, score3;
        sscanf(scoreStr.c_str(), "%d %d %d", &score1, &score2, &score3);

        int totalScore = score1 + score2 + score3;
        char grade = score2grade(totalScore);

        names.push_back(name);
        scores.push_back(totalScore);
        grades.push_back(grade);
    }

    file.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command: \n";
    getline(cin, command);

    size_t spacePos = command.find(" ");
    if(spacePos != string::npos){
        key = command.substr(spacePos + 1);
        command = command.substr(0, spacePos);
    } else {
        key = "";
    }
}

void searchName(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key){
    bool found = false;
    for(size_t i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            found = true;
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            break;
        }
    }
    if(!found){
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key){
    bool found = false;
    for(size_t i = 0; i < grades.size(); i++){
        if(grades[i] == key[0]){
            if(!found) cout << "---------------------------------\n";
            found = true;
            cout << names[i] << " (" << scores[i] << ")\n";
        }
    }
    if(!found){
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    } else {
        cout << "---------------------------------\n";
    }
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
