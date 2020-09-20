#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void R1_levels(int max, int level){
    cout << setw(level+33) << "This was written by call number "  << level << endl;
    if(level<max){ //base case
        R1_levels(max, level+1);
    }
    cout << setw(level+33) << "This ALSO written by call number " << level << endl;
}

void R1_test(){
    R1_levels(5, 0); //0 to 5 and back again
}

void R2_box(string prefix, unsigned int levels){
    if (levels == 0){ //base case
        cout << prefix << endl;
        return;
    }
    else{
        for(int i = 1; i < 10; i++){
            string s = prefix;
            s += char('0' +i); //appending number
            s += '.';
            R2_box(s, levels - 1); //recursive call with one less level
        }
    }
}

void R2_test(){
    R2_box("BOX:", 3); //3 levels with prefix BOX: (1.1.1. through 9.9.9.)
}

void R3_first_second(string first, string second){
    if(first.size() == 0){ //base case, when first string's size is 0
        cout << first + second << endl;
    }
    else{
        for(int i = 0; i < first.size(); i++){
            char temp = first[i];
            first.erase(i,1);
            first.insert(first.size()-i, 1, temp);
            R3_first_second(first, second);
        }
    }
}

int box_count = 0;
void R4_boxes(string s, int boxes){
    for(int i = 1; i <= boxes; i++){
        int boxes_in_box;
        cout << "How many boxes are in box " << s << i << ":";
        cin >> boxes_in_box;
        box_count++;
        if(boxes_in_box != 0){ //while there are boxes to process
            s += char('0' + i); //append interior box data
            s += '.';
            R4_boxes(s, boxes_in_box);
            s = s.substr(0, s.size()-2);
        }
    }
}

void R4_test(){
    int boxes;
    cout << "How many unnumbered boxes can you see? ";
    cin >> boxes;

    string s;

    R4_boxes(s, boxes);
    cout << "Total number of boxes: " << box_count << endl;
    system("PAUSE");
}

double R5_sumover(unsigned int n){
    if(n==0){
        return 0;
    }
    else{
        return (1.0/n + R5_sumover(n-1.0)); //sum of reciprocals
    }
}

void R5_test(){
    unsigned int n;
    cout << "Sum of Reciprocals" << endl << "Enter number: ";
    cin >> n;
    double result = R5_sumover(n);
    cout << "Result: " << result << endl;
}

void R16_guess_number(int low, int high){ //Implementing Binary Search
    int mid = ((high+low)/2);
    char ans;
    cout << "Is your number: " << mid << "? (y/n)" << endl;
    cin >> ans;
    cout << endl;
    if(ans == 'y'){ //Found number, return
        cout << "Nice" << endl;
        return;
    }
    else{
        cout << "Is your number larger than " << mid << "? (y/n)" << endl;
        cin >> ans;
        cout << endl;
        if(ans == 'y'){
            R16_guess_number(mid+1, high); //Higher than guess
        }
        else{
            R16_guess_number(low, mid-1); //Lower than guess
        }
    }
}

void R16_test(){
    int maxnum = 1000000;
    cout << "Guess a number between 1 and " << maxnum << endl;
    R16_guess_number(1, maxnum);
}

int main(){
    //R1_test();
    //R2_test();
    //R3_first_second("CAT", "MAN");
    //R4_test();
    //R5_test();
    //R16_test();
    system("PAUSE");
}