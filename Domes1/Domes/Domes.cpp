// Domes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>  
#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include <string>
#include <sstream>  
#include <cstdlib>
#include "ChainNode.h"
#include "Chain.h"
#include "Views.h"
#include "ChainIterator.h"

using namespace std;
void SetValues(Chain<Views>* AllViews, int *SomeData, string fname);
bool Check(Chain<Views>* tours, int index, Views* view, int day);
float Benefit(Chain<Views>* tours, int index, Views* view);

int main()
{
	int SomeData[3];		//ΠΛΗΘΟΣ ΤΑΞΙΔΙΩΝ, ΗΜΕΡΑ ΕΝΑΡΞΗΣ, ΑΡΙΘΜΟ ΠΡΟΟΡΙΣΜΩΝ
	Chain<Views> *AllViews = new Chain<Views>;		//ΟΛΟΙ ΟΙ ΠΡΟΟΡΙΣΜΟΙ
	string fname;
	int choice;
	cout << "Press: \n1 for t112.txt\n2 for t136.txt\n3 for t145.txt" << endl;
	cin >> choice;
	switch (choice)
	{
	case(1):
		fname = "t112.txt";
		break;
	case(2):
		fname = "t136.txt";
		break;
	case(3):
		fname = "t145.txt";
		break;
	}
	SetValues(AllViews, SomeData,fname);		//ΚΑΤΑΧΩΡΗΣΗ ΔΕΔΟΜΕΝΩΝ
	Chain<Views>** Tours = new Chain<Views>*[SomeData[0]];		//ΠΙΝΑΚΑΣ ΜΕ POINTER ΓΙΑ ΚΑΘΕ ΤΑΞΙΔΙ
	ChainIterator<Views> *pointViews = new ChainIterator<Views>;
	Views *CurView = pointViews->Initialize(*AllViews);		//ΑΡΧΙΚΟΠΟΙΗΣΗ POINTER ΣΤΟ ΠΡΩΤΟ ΣΤΟΙΧΕΙΟ ΚΑΙ ΕΠΙΣΤΡΟΦΗ ΤΟΥ
	CurView = pointViews->Next();		//ΜΕΤΑΚΙΝΗΣΗ POINTER ΣΤΟ ΑΜΕΣΩΣ ΕΠΟΜΕΝΟ ΣΤΟΙΧΕΙΟ ΚΑΙ ΕΠΙΣΤΡΟΦΗ ΤΟΥ
	for (int i = 0; i < SomeData[0]; i++) {		//ΑΡΧΙΚΟΠΟΙΗΣΗ ΤΑΞΙΔΙΩΝ ΜΕ ΠΡΩΤΟ ΚΑΙ ΤΕΛΕΥΤΑΙΟ ΠΡΟΟΡΙΣΜΟ ΤΟ ΞΕΝΟΔΟΧΕΙΟ
		Tours[i] = new Chain<Views>;
		Tours[i]->Insert(0, *CurView);
		Tours[i]->Insert(1, *CurView);
		
	}
	Views *hotel = new Views;
	*AllViews = AllViews->Delete(2, *hotel);	//ΔΙΑΓΡΑΦΗ ΞΕΝΟΔΟΧΕΙΟΥ ΑΠΟ ΤΗ ΛΙΣΤΑ ΜΕ ΤΟΥΣ ΠΡΟΟΡΙΣΜΟΥΣ
	int iterations;
	cout << "Dose arithmo epanalipseon." << endl;
	cin >> iterations;
	for (int k = 0; k < iterations; k++) {	
		bool AllFull = false;
		while (!AllFull) {	//ΕΛΕΓΧΟΣ ΑΝ ΔΕΝ ΥΠΑΡΧΕΙ ΑΛΛΗ ΔΥΝΑΤΗ ΕΠΕΚΤΑΣΗ
			CurView = pointViews->Initialize(*AllViews);
			for (int j = 0; j < AllViews->Length(); j++) {	//ΧΡΗΣΙΜΕΥΕΙ ΣΤΟΝ ΠΑΡΑΠΑΝΩ ΕΛΕΓΧΟ
				CurView->capable = false;
				CurView = pointViews->Next();
			}
			float MaxBenefit = -1.0;	//ΜΕΓΙΣΤΟ ΟΦΕΛΟΣ
			int MaxIndex;
			int MaxT;
			Views *MaxView = new Views;
			int day = SomeData[1];
			for (int t = 0; t < SomeData[0]; t++){
				ChainIterator<Views> *pointViT = new ChainIterator<Views>;	//ViT: ΑΞΙΟΘΕΑΤΟ ΠΟΥ ΕΛΕΓΧΕΤΑΙ ΓΙΑ ΕΙΣΑΓΩΓΗ
				Views *ViT;
				int index = 1;
				while (index < Tours[t]->Length() && AllViews->Length()>0) {
					ViT = pointViT->Initialize(*AllViews);
					for (int k = 0; k < AllViews->Length(); k++) {
						if (Check(Tours[t], index, ViT, day)) {	//ΕΛΕΓΧΟΣ ΕΙΣΑΓΩΓΗΣ
							ViT->capable = true;
							float curBen = Benefit(Tours[t], index, ViT);	//ΥΠΟΛΟΓΙΣΜΟΣ ΟΦΕΛΟΥΣ
							if (MaxBenefit < curBen) {	//ΕΥΡΕΣΗ ΜΕΓΙΣΤΟΥ ΟΦΕΛΟΥΣ
								MaxBenefit = curBen;
								MaxView = ViT;
								MaxT = t;
								MaxIndex = index;
							}
						}
						ViT = pointViT->Next();
					}
					index++;
				}
				day++;
				if (day == 7) {
					day = 0;
				}
			}
			if (MaxT>=0){
				Tours[MaxT]->Insert(MaxIndex, *MaxView);	//ΤΟΠΟΘΕΤΗΣΗ ΠΡΟΟΡΙΣΜΟΥ ΣΕ ΤΑΞΙΔΙ
				CurView = pointViews->Initialize(*AllViews);
				for (int k = 0; k < AllViews->Length(); k++) {
					if (CurView->id == MaxView->id) {
						*AllViews = AllViews->Delete(k, *CurView); //ΔΙΑΓΡΑΦΗ ΤΟΥ ΑΝΤΙΣΤΟΙΧΟΥ ΠΡΟΟΡΙΣΜΟΥ ΑΠΟ ΤΗ ΛΙΣΤΑ ΜΕ ΟΛΟΥΣ ΤΟΥΣ ΠΡΟΟΡΙΣΜΟΥΣ
						break;
					}
					CurView = pointViews->Next();
				}
			}
			CurView = pointViews->Initialize(*AllViews);
			for (int j = 0; j < AllViews->Length(); j++) { //ΑΝ ΥΠΑΡΧΟΥΝ ΠΡΟΟΡΙΣΜΟΙ ΑΞΙΟΙ ΓΙΑ ΤΟΠΟΘΕΣΤΗΣΗ ΒΑΣΕΙ ΤΗΣ ΣΥΝΑΡΤΗΣΗΣ
				if (CurView->capable == true) {			   // CHECK ΤΟΤΕ ΣΥΝΕΧΙΖΕΤΑΙ Ο ΕΛΕΓΧΟΣ ΚΑΙ Η ΤΟΠΟΘΕΤΗΣΗ
					AllFull = false;
				}
				else {
					AllFull = true;
					break;
				}
			}
			cout << "Dose syntelesti. " << endl;
			float factor;
			cin >> factor;
			for (int j = 0; j < SomeData[0]; j++) {	//ΔΙΑΓΡΑΦΗ ΠΡΟΟΡΙΣΜΩΝ ΚΑΘΕ ΤΑΞΙΔΙΟΥ
				int deleteViews = (int)factor*(Tours[j]->Length());	//ΠΛΗΘΟΣ ΠΡΟΟΡΙΣΜΩΝ ΠΟΥ ΘΑ ΔΙΑΓΡΑΦΤΟΥΝ
				int startDelete = rand() % Tours[j]->Length() + 1;	//ΕΠΙΛΟΓΗ ΤΥΧΑΙΟΥ ΠΡΟΟΡΙΣΜΟΥ
				CurView = pointViews->Initialize(*Tours[j]);
				for (int j = 1; j < startDelete; j++) {
					CurView = pointViews->Next();
				} 
				int del = startDelete;
				while (deleteViews>0) {
					if (del < Tours[j]->Length()) {
						Tours[j]->Delete(del, *CurView);
						AllViews->Append(*CurView);
						CurView = pointViews->Next();
					}
					else {
						del = 0;
						CurView = pointViews->Initialize(*Tours[j]);
						CurView = pointViews->Next();
					}
					del++;
					deleteViews--;
				}
			}
		}

	}
	cout << "Ta taxidia einai ta exis:" << endl;
	for (int i = 0; i <SomeData[0]; i++) {	//ΕΚΤΥΠΩΣΗ ΤΑΞΙΔΙΩΝ, ID ΠΡΟΟΡΙΣΜΩΝ
		CurView = pointViews->Initialize(*Tours[i]);
		for (int j = 0; j < Tours[i]->Length(); j++) {
			cout << CurView->id << " ";
			CurView = pointViews->Next();
		}
		cout << endl;
	}
	system("PAUSE");
    return 0;
}


void SetValues(Chain<Views>* AllViews, int SomeData[3],string fname) {
	ifstream file;
	string s;
	file.open(fname, ios::in);
	int i = 0;
	while (getline(file,s)) {
		Views *Cur_View = new Views;
		stringstream iss(s);
		if (i == 0) {	//ΑΠΟΘΗΚΕΥΣΗ ΔΕΔΟΜΕΝΩΝ ΣΕ SOMEDATA
			for (int k = 0; k < 4; k++) {
				int x;
				iss >> x;
				if (k != 0) {
					SomeData[k - 1] = x;
				}
			}
			i++;
		}
		else if (i == 1) {	//ΑΠΟΘΗΚΕΥΣΗ ΔΕΔΟΜΕΝΩΝ ΞΕΝΟΔΟΧΕΙΟΥ
			int id, x, y, d, s, o, c;
			iss >> id >> x >> y >> d >> s >> o >> c;
			Cur_View->SetId(id);
			Cur_View->SetCoords(0, (float)x);
			Cur_View->SetCoords(1, (float)y);
			Cur_View->SetAverage(d);
			Cur_View->SetGrade(s);
			Cur_View->SetOpen(0, o);
			Cur_View->SetClose(0, c);
			i++;
		}
		else {	//ΑΠΟΘΗΚΕΥΣΗ ΔΕΔΟΜΕΝΩΝ ΠΡΟΟΡΙΣΜΩΝ
			int id, d, s, t, o, c;
			float x, y;
			iss >> id >> x >> y >> d >> s >> t;
			Cur_View->SetId(id);
			Cur_View->SetCoords(0, x);
			Cur_View->SetCoords(1, y);
			Cur_View->SetAverage(d);
			Cur_View->SetGrade(s);
			for (int k = 0; k < 7; k++) {
				iss >> o >> c;
				Cur_View->SetOpen(k, o);
				Cur_View->SetClose(k, c);
			}
			i++;
		}
		if (i > 0) {	//ΕΙΣΑΓΩΓΗ ΣΕ ΛΙΣΤΑ
			AllViews->Insert(i - 1, *Cur_View);	
		}
	}
	
}

bool Check(Chain<Views>* tours, int index, Views* view, int day) {
	Chain<Views> *nTour = new Chain<Views>(*tours);	//COPY CONSTRUCTOR
	nTour->Insert(index, *view);	//ΕΙΣΑΓΩΓΗ ΥΠΟΨΗΦΙΟΥ ΠΡΟΟΡΙΣΜΟΥ ΣΕ ΘΕΣΗ ΟΠΟΥ ΓΙΝΕΤΑΙ Ο ΕΛΕΓΧΟΣ
	ChainIterator<Views> *y = new ChainIterator<Views>;
	Views *curView;
	Views *nextView;
	curView = y->Initialize(*nTour);
	nextView = y->Next();
	float dur = (float)(curView->Open(0));
	for (int i = 0; i < nTour->Length()-2; i++) {
		dur += curView->Distance(nextView);
		if (dur < nextView->Open(day)) {	//ΑΦΙΞΗ ΠΡΙΝ ΤΗΝ ΩΡΑ ΠΟΥ ΑΝΟΙΓΕΙ
			dur = (float)(nextView->Open(day) + nextView->average);
		}
		else if (dur + nextView->average <= nextView->Close(day)) {	//ΑΦΙΞΗ ΚΑΙ ΕΠΙΣΚΕΨΗ ΠΡΙΝ ΤΗΝ ΩΡΑ ΠΟΥ ΚΛΕΙΝΕΙ
			dur +=(float)(nextView->average);
		}
		else {
			return false;
		}
		curView = nextView;
		nextView = y->Next();
	}
	dur +=(float)(curView->Distance(nextView));
	if (dur > nextView->Close(0)) {	//ΕΛΕΓΧΟΣ ΑΝ Η ΔΙΑΡΚΕΙΑ ΕΙΝΑΙ ΜΙΚΡΟΤΕΡΗ ΑΠΟ ΤΗΝ ΩΡΑ ΠΟΥ ΔΙΑΘΕΤΕΙ
		return false;
	}
	return true;
}

float Benefit(Chain<Views>* tours, int index, Views* view) { //ΥΠΟΛΟΓΙΣΜΟΣ ΟΦΕΛΟΥΣ ΒΑΣΕΙ ΤΥΠΟΥ
	ChainIterator<Views> *y = new ChainIterator<Views>;
	Views *prev = new Views;
	Views *next = new Views;
	prev = y->Initialize(*tours);
	next = y->Next();
	for (int i = 1; i < index; i++) {
		prev = next;
		next = y->Next();
	}
	return (float)(pow((double)(view->grade), 2.0) / (view->average + prev->Distance(view) +
			view->Distance(next) - prev->Distance(next)));	
}




