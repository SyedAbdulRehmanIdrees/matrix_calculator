#include <iostream>
using namespace std;

const int rows = 3;
const int cols = 3;
int A[rows][cols];
int B[rows][cols];
int C[rows][cols];

bool myStrCmp(string, string, int, int);
string slice(string, int, int);
string removeChar(string, char);
string getField(string, int);
bool isValidMatrixName(char);
bool isValidOp(char);
bool isNumber(string, int);
int convertToInt(string);
void parseLine(string);
void print(char);
void assign(char, string);

bool isIdentity(char);
bool isDiagonal(char);
bool isSymmetric(char);

void transpose(char);
void matrixAddition(char, char);
void matrixSubtraction(char, char);
void matrixMultiplication(char, char);
void scalarMultiplication(int, char);

int main(){
    string line;

    while(line != "Exit"){
        cout << ">> ";
        getline(cin, line);

        parseLine(removeChar(line, ' '));
    }
}

void parseLine(string input){
    char matrix;
    if(myStrCmp(input, "print(", 0, 6) && input[7] == ')'){
        matrix = input[6];

        if(isValidMatrixName(matrix)){
            print(matrix);
        }
        else {
            cout << "Invalid matrix name" << endl;
        }
    }
    else if(myStrCmp(input, "isIdentity(", 0, 11) && input[12] == ')'){
        matrix = input[11];

        if(isValidMatrixName(matrix)){
            cout << isIdentity(matrix) << endl;
        }
        else {
            cout << "Invalid matrix name" << endl;
        }
    }
    else if(myStrCmp(input, "transpose(", 0, 10) && input[11] == ')'){
        matrix = input[10];

        if(isValidMatrixName(matrix)){
            transpose(matrix);
        }
        else {
            cout << "Invalid matrix name" << endl;
        }
    }
    else if(myStrCmp(input, "isDiagonal(", 0, 11) && input[12] == ')'){
        matrix = input[11];

        if(isValidMatrixName(matrix)){
            cout << isDiagonal(matrix) << endl;
        }
        else {
            cout << "Invalid matrix name" << endl;
        }
    }
    else if(myStrCmp(input, "isSymmetric(", 0, 12) && input[13] == ')'){
        matrix = input[12];

        if(isValidMatrixName(matrix)){
            cout << isSymmetric(matrix) << endl;
        }
        else {
            cout << "Invalid matrix name" << endl;
        }
    }
    else if(isValidMatrixName(input[0]) && input[1] == '=' && input[2] == '{' && input[input.length()-1] == '}'){
        assign(input[0], slice(input, 3, input.length() - 1));
    }
    else if(isValidMatrixName(input[0]) && input[1] == '=' && isValidMatrixName(input[2]) && isValidOp(input[3]) && isValidMatrixName(input[4])){
        if(input[3] == '+'){
            matrixAddition(input[2], input[4]);
        }
        else if(input[3] == '-'){
            matrixSubtraction(input[2], input[4]);
        }
        else if(input[3] == '*'){
            matrixMultiplication(input[2], input[4]);
        }
    }
    else if(isValidMatrixName(input[0]) && input[1] == '=' && isNumber(input, 2) && input[input.length()-2] == '*' && isValidMatrixName(input[input.length()-1])){
        scalarMultiplication(convertToInt(slice(input, 2, input.length() - 2)), input[input.length() - 1]);
    }
    else {
        cout << "Invalid input" << endl;
    }
}

bool myStrCmp(string s1, string s2, int a, int b){
    int x = 0;
    if(a < 0 || a >= s1.length() || b < 0 || b > s1.length() || (b - a) > s2.length()){
        return false;
    }

    for(int i = a; i < b; i++, x++){
        if(s1[i] != s2[x]){
            return false;
        }
    }

    return true;
}

string slice(string s, int a, int b){
    string tmp = "";

    for(int i = a; i < b; i++){
        tmp += s[i];
    }

    return tmp;
}

void print(char m){
    if(m == 'A'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
    }
    else if(m == 'B'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                cout << B[i][j] << " ";
            }
            cout << endl;
        }
    }
    else if(m == 'C'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                cout << C[i][j] << " ";
            }
            cout << endl;
        }
    }
}

bool isIdentity(char m){
    if(m == 'A'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(i == j){
                    if(A[i][j] != 1){
                        return false;
                    }
                }
                else {
                    if(A[i][j] != 0){
                        return false;
                    }
                }
            }
        }
    }
    else if(m == 'B'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(i == j){
                    if(B[i][j] != 1){
                        return false;
                    }
                }
                else {
                    if(B[i][j] != 0){
                        return false;
                    }
                }
            }
        }
    }
    else if(m == 'C'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(i == j){
                    if(C[i][j] != 1){
                        return false;
                    }
                }
                else {
                    if(C[i][j] != 0){
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

bool isDiagonal(char m){
    int nonZeroDiagonal = 0;

    if(m == 'A'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(i == j){
                    if(A[i][j] != 0){
                        nonZeroDiagonal++;
                    }
                }
                else {
                    if(A[i][j] != 0){
                        return false;
                    }
                }
            }
        }
    }
    else if(m == 'B'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(i == j){
                    if(B[i][j] != 0){
                        nonZeroDiagonal++;
                    }
                }
                else {
                    if(B[i][j] != 0){
                        return false;
                    }
                }
            }
        }
    }
    else if(m == 'C'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(i == j){
                    if(C[i][j] != 0){
                        nonZeroDiagonal++;
                    }
                }
                else {
                    if(C[i][j] != 0){
                        return false;
                    }
                }
            }
        }
    }

    if(nonZeroDiagonal > 0){
        return true;
    }
    else {
        return false;
    }
}

bool isSymmetric(char m){
    if(m == 'A'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(A[i][j] != A[j][i]){
                    return false;
                }
            }
        }
    }
    else if(m == 'B'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(B[i][j] != B[j][i]){
                    return false;
                }
            }
        }
    }
    else if(m == 'C'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(C[i][j] != C[j][i]){
                    return false;
                }
            }
        }
    }

    return true;
}

void transpose(char m){
    if(m == 'A'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                C[i][j] = A[j][i];
            }
        }
    }
    else if(m == 'B'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                C[i][j] = B[j][i];
            }
        }
    }
    else if(m == 'C'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                C[i][j] = C[j][i];
            }
        }
    }
}

void matrixAddition(char m1, char m2){
    if((m1 == 'A' && m2 == 'B') || (m1 == 'B' && m2 == 'A')){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                C[i][j] = A[i][j] + B[i][j];
            }
        }
    }
    else if((m1 == 'A' && m2 == 'C') || (m1 == 'C' && m2 == 'A')){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                C[i][j] = A[i][j] + C[i][j];
            }
        }
    }
    else if((m1 == 'C' && m2 == 'B') || (m1 == 'B' && m2 == 'C')){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                C[i][j] = C[i][j] + B[i][j];
            }
        }
    }
}

void matrixSubtraction(char m1, char m2){
    if(m1 == 'A' && m2 == 'B'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                C[i][j] = A[i][j] - B[i][j];
            }
        }
    }
    else if(m1 == 'B' && m2 == 'A'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                C[i][j] = B[i][j] - A[i][j];
            }
        }
    }
    else if(m1 == 'A' && m2 == 'C'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                C[i][j] = A[i][j] - C[i][j];
            }
        }
    }
    else if(m1 == 'C' && m2 == 'A'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                C[i][j] = C[i][j] - A[i][j];
            }
        }
    }
    else if(m1 == 'B' && m2 == 'C'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                C[i][j] = B[i][j] - C[i][j];
            }
        }
    }
    else if(m1 == 'C' && m2 == 'B'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                C[i][j] = C[i][j] - B[i][j];
            }
        }
    }
}

void scalarMultiplication(int k, char m){
    if(m == 'A'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                C[i][j] = k * A[i][j];
            }
        }
    }
    else if(m == 'B'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                C[i][j] = k * B[i][j];
            }
        }
    }
    else if(m == 'C'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                C[i][j] = k * C[i][j];
            }
        }
    }
}

void matrixMultiplication(char m1, char m2){
    int sum = 0;

    if(m1 == 'A' && m2 == 'B'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                sum = 0;

                for(int k = 0; k < cols; k++){
                    sum += A[i][k] * B[k][j];
                }

                C[i][j] = sum;
            }
        }
    }
    else if(m1 == 'B' && m2 == 'A'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                sum = 0;

                for(int k = 0; k < cols; k++){
                    sum += B[i][k] * A[k][j];
                }

                C[i][j] = sum;
            }
        }
    }
    else if(m1 == 'A' && m2 == 'C'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                sum = 0;

                for(int k = 0; k < cols; k++){
                    sum += A[i][k] * C[k][j];
                }

                C[i][j] = sum;
            }
        }
    }
    else if(m1 == 'C' && m2 == 'A'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                sum = 0;

                for(int k = 0; k < cols; k++){
                    sum += C[i][k] * A[k][j];
                }

                C[i][j] = sum;
            }
        }
    }
    else if(m1 == 'B' && m2 == 'C'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                sum = 0;

                for(int k = 0; k < cols; k++){
                    sum += B[i][k] * C[k][j];
                }

                C[i][j] = sum;
            }
        }
    }
    else if(m1 == 'C' && m2 == 'B'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                sum = 0;

                for(int k = 0; k < cols; k++){
                    sum += C[i][k] * B[k][j];
                }

                C[i][j] = sum;
            }
        }
    }
}

void assign(char m, string values){
    if(m == 'A'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                A[i][j] = convertToInt(getField(values, i * 3 + j));
            }
        }
    }
    else if(m == 'B'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                B[i][j] = convertToInt(getField(values, i * 3 + j));
            }
        }
    }
    else if(m == 'C'){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                C[i][j] = convertToInt(getField(values, i * 3 + j));
            }
        }
    }
}

string getField(string record, int field){
    int seps = 0;
    string ret = "";
    char sep = ',';

    for(int i = 0; i < record.length(); i++){
        if(record[i] == sep){
            seps++;
            continue;
        }
        else if(seps == field){
            ret += record[i];
        }
        else if(seps > field){
            break;
        }
    }

    return ret;
}

int convertToInt(string orig){
    int n = 0, idx = 0;
    int sign = 1;
    bool signChecked = false;

    while(orig[idx] != '\0'){
        if(orig[idx] == ' '){
            continue;
        }

        if((orig[idx] == '-' || orig[idx] == '+') && !signChecked){
            if(orig[idx] == '-'){
                sign = -1;
            }

            signChecked = true;
        }
        else if(orig[idx] >= '0' && orig[idx] <= '9'){
            n = n * 10 + orig[idx] - '0';
        }
        else {
            break;
        }

        idx++;
    }

    return sign * n;
}

bool isValidMatrixName(char m){
    return m >= 'A' && m <= 'C';
}

bool isValidOp(char op){
    return op == '+' || op == '-' || op == '*';
}

bool isNumber(string line, int start){
    for(int i = start; i < line.length(); i++){
        if(isValidOp(line[i])) break;
        
        if(!(line[i] >= '0' && line[i] <= '9')){
            cout << line[i] << endl;
            return false;
        }
    }

    return true;
}

string removeChar(string s, char c){
    string tmp = "";

    for(int i = 0; i < s.length(); i++){
        if(s[i] == c) continue;

        tmp += s[i];
    }

    return tmp;
}
