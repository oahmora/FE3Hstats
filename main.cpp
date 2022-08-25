#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

void displayArray(string, int *, string *, int, string);
void displayArray(string, float *, string *, int, string);
void inputData(ifstream &, string, int *);
void newSort(int *, int);

const int STATS = 9;

int main(int argc, char** argv)
{
    srand (time(NULL));
    
    //Change these
    string name = "Edelgard";
    string class1 = "Noble";
    string class2 = "Fighter";
    string class3 = "Brigand";
    string class4 = "WyvernRider";
    string class5 = "FalconKnight";
	int classPath;
    int level = 20;
    int iterations = 10000;       //the higher, the more accurate
	int percentile = 85;
    
    //Do not change these
    string statNameArray[STATS] = {"HP ", "Str", "Mag", "Dex", "Spd", "Lck", "Def", "Res", "Cha"};
    int growthArray[STATS];
    int basesArray[STATS];
    int avgArray[STATS] = {0};
    int lvlArray[iterations][STATS];
    int class1Ary[STATS];
    int class2Ary[STATS];
    int class3Ary[STATS];
    int class4Ary[STATS];
    int class5Ary[STATS];
	
	name = argv[1];
	level = atof(argv[2]);
	classPath = atof(argv[3]);
	
	switch(classPath){
		case 1:
			class3 = "Brigand", class4 = "Grappler", class5 = "WarMaster";
			break;
		case 2:
			class3 = "Brigand", class4 = "WyvernRider", class5 = "WyvernLord";
			break;
		case 3:
			class3 = "PegasusKnight", class4 = "WyvernRider", class5 = "FalconKnight";
			break;
		case 4:
			class3 = "Mercenary", class4 = "Assassin", class5 = "Assassin";
			break;
		case 5:
			class3 = "Mercenary", class4 = "Swordmaster", class5 = "Swordmaster";
			break;
		case 6:
			class3 = "ArmoredKnight", class4 = "FortressKnight", class5 = "GreatKnight";
			break;
		case 7:
			class2 = "Monk", class3 = "Mage", class4 = "Warlock", class5 = "Gremory";
			break;
		case 8:
			class2 = "Monk", class3 = "Mage", class4 = "Valkyrie", class5 = "Valkyrie";
			break;
		case 9:
			class2 = "Monk", class3 = "Mage", class4 = "Valkyrie", class5 = "DarkFlier";
			break;
		case 10:
			class3 = "Mercenary", class4 = "Trickster", class5 = "Trickster";
			break;
		case 11:
			class3 = "Brigand", class4 = "WarMonk", class5 = "WarMonk";
			break;
	}
    
    //cout<<"Has your character been RNG screwed? Let's calculate. Enter character and their level.\n";
    //cin>>name;
	//cin>>level;
	
    ifstream growth ("growth.txt");
    ifstream bases ("bases.txt");
    ifstream classGrowths("classGrowths.txt");
    inputData(growth, name, growthArray);
    inputData(bases, name, basesArray);
    inputData(classGrowths, class1, class1Ary);
    inputData(classGrowths, class2, class2Ary);
    inputData(classGrowths, class3, class3Ary);
    inputData(classGrowths, class4, class4Ary);
    inputData(classGrowths, class5, class5Ary);
    //displayArray(class1, class1Ary, statNameArray);
    //displayArray(class2, class2Ary, statNameArray);
    //displayArray(class3, class3Ary, statNameArray);
    //displayArray(class4, class4Ary, statNameArray);
    //displayArray(class5, class5Ary, statNameArray);
    
    for(int k = 0; k < iterations; k++){
        for(int i = 0; i<STATS; i++){
            lvlArray[k][i] = basesArray[i];
            for(int j = 0; j < level; j++){
                switch((j/10)+2){
                    case 3: 
                        if(rand() % 100 <= (growthArray[i] + class3Ary[i])){
                            lvlArray[k][i]++;
                        }
                        break;
                    case 4:
                        if(rand() % 100 <= (growthArray[i] + class4Ary[i])){
                            lvlArray[k][i]++;
                        }
                        break;
                    case 5:
                        if(rand() % 100 <= (growthArray[i] + class5Ary[i])){
                            lvlArray[k][i]++;
                        }
                        break;
                    case 2: 
                        if(j>=5 && j<10){
                            if(rand() % 100 <= (growthArray[i] + class2Ary[i])){
                                lvlArray[k][i]++;
                            }
                            break;
                        }
                    default:
                        if(rand() % 100 <= (growthArray[i])){
                            lvlArray[k][i]++;
                        }
                        break;
                }
            }
        }
    }
    
	float varArray[STATS] = {0};
	
    for(int i = 0; i < STATS; i++){
        for(int k = 0; k < iterations; k++){
            avgArray[i] += lvlArray[k][i];
        }
        avgArray[i] /= iterations;
    }
	
	for(int i = 0; i < STATS; i++){
		float temp = 0;
        for(int k = 0; k < iterations; k++){
            temp = (lvlArray[k][i] - avgArray[i]);
			temp *= temp;
			varArray[i] += temp;
        }
        varArray[i] /= (iterations - 1);
    }
	displayArray("Standard Deviation", varArray, statNameArray, level, class5);
    
    displayArray(name, avgArray, statNameArray, level, class5);
    
}

//////////////////////////////////////////
//  Display Array
/////////////////////////////////////////
void displayArray(string name, int array[STATS], string nameArray[STATS], int level, string class5){
    cout << endl << name << " LVL "<< level << " " << class5 << endl;
    for(int i = 0; i<STATS; i++){
        cout << nameArray[i] << ": " << array[i] << "   ";
        if((((i+1)%3) == 0)) cout<<endl;
    }
}
void displayArray(string name, float array[STATS], string nameArray[STATS], int level, string class5){
    cout << endl << name << " LVL "<< level << " " << class5 << endl;
    for(int i = 0; i<STATS; i++){
        cout << nameArray[i] << ": " << array[i] << "   ";
        if((((i+1)%3) == 0)) cout<<endl;
    }
}
//////////////////////////////////////////
//  Input Data from File
/////////////////////////////////////////
void inputData(ifstream & file, string name, int array[STATS]){
    string nameTemp;  //to scan file until name is found
    
    file.clear();
    file.seekg(0, ios::beg);
    
    while( file >> nameTemp){
        for(int i = 0; i<STATS; i++){
            file >> array[i];
        }
        if(name == nameTemp) return;
    }
}