#include <iostream>
#include <cmath>// pow()
#include <vector>
using namespace std; 

//Declare a new variable type: vector of ints.
typedef vector<int> Tower;

void move(Tower &from, Tower &to, Tower &extra, int &count){
	
	static int last_ring=0; // This variable keeps track of the most recently moved ring
	
	if( from.back() == last_ring) // if there's an attempt to move the same ring 2x in a row, get out
		return;
		
	for(int i=0; i < from.size()-1; i++){ // Try to move as many rings as possible before moving to next tower
		//Check whether the the ring in the 'to' tower is smaller than the one being moved. 
		if( from.back() < to.back() ){
			to.push_back(from.back());
			from.pop_back();
			cout << "Move ring " << to.back() << " from tower " << char(from.front() ) << " to tower "<< char(to.front() ) << endl;
			last_ring = to.back();
			count++;
		}
		
		else if( from.back() < extra.back()){
			extra.push_back(from.back());
			from.pop_back();
			cout << "Move ring " << extra.back() << " from tower " << char(from.front() ) << " to tower "<< char(extra.front() ) << endl;
			last_ring = extra.back();
			count++;
		}
	}
}

int main(){ 
	int rings, move_right=0, move_left=0, count= 0;
	
	cout << "Enter number of rings: ";
	cin >> rings;

	// Create 3 towers (empty vectors) and differentiate them by their first element ("identifier")
	Tower A (1, 65); // 65 is 'A' in the ASCII table...
	Tower B (1, 66);
	Tower C (1, 67);
	
	// Place the rings on Tower A.
	for(int i=rings; i >= 1; i--)
		A.push_back(i);

	while( count < (pow<int>(2,rings) -1 ) ){
		
		if( rings%2 != 0){// Check whether 'rings' is odd, if true move to the right
			switch(move_right){ 
				case 0:
					move(A, B, C, count);
					move_right=1;
					break;
				case 1:
					move(B, C, A, count);
					move_right=2;
					break;
				default:
					move(C, A, B, count);
					move_right=0;
					break;
			}
		}
		else{ // 'rings' is even, move to the left
			switch(move_left){
				case 0:
					move(A, C, B, count);
					move_left=1;
					break;
				case 1:
					move(C, B, A, count);
					move_left=2;
					break;
				default:
					move(B, A, C, count);
					move_left=0;
					break;
			}
		}
	}
	cout << endl << "Moves: " << count << endl;
	return 0;
}
