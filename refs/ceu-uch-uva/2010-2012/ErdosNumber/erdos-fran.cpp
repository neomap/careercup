/**
 * Erdös numbers
 * Problem #10044
 **/
 
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class nodeList
{	
	public:
		int lvl;
		vector <string> names;
		
		nodeList()
		{
			
		}
};

class firstList
{
	public:
		int pos;
		vector<nodeList> list;
		vector<nodeList> orderedList;
		nodeList aux;
		
		//From the whole string, put the names in a vector and return it
		vector<string> makeNames(string line)
		{
			int x = 0;
			int from = 0;
			int to = 0;
			bool comma = false;					//We (always?) break after comma #2
			vector <string> toReturn;
			
			//Separate line names and put them into toReturn
			while(line[x]!=':')
			{
				comma = false;
				
				//We find a name
				for(x = from; (!(line[x]==',' && comma) && line[x]!=':'); ++x)
				{
					if(line[x]==',' && !comma)	
						comma = true;
				}
				
				to = x;
				
				//Put it in the vector of names
				if(comma)
					toReturn.push_back(line.substr(from, to-from));
				
				from = to+2;
			}	
				
			return toReturn;
		}
		
		bool makeLevel(vector<string> &alreadyUsed, nodeList &toInsert, vector<string> &from)
		{
			//If the names in his set aren't already on the list
					//madeAny=true;
					//Add name to new level
					//Add name to alreadyUsed
					//k = list[j].names.size(); Because we don't need to look further in that level
			bool used = false;
			bool anyMade = false;
			
			for(unsigned int i = 0; i<from.size(); ++i)
			{
				used = false;
				
				for(unsigned int j = 0; j<alreadyUsed.size(); ++j)
					if(from[i].compare(alreadyUsed[j])==0)
						used = true;
				
				if(!used)
				{
					toInsert.names.push_back(from[i]);
					//cout << "Inserting " << from[i] << endl;
					alreadyUsed.push_back(from[i]);
					anyMade = true;
				}
			}
			
			from.clear();				//When I didn't have this line I got Wrong Answer. I added it and got accepted. This is a GREAT line.
			return anyMade;
		}
		
	//public:
		//Constructor
		firstList()
		{	pos = 0;	}
		
		//Function to insert a new line
		void insertLine(string line)
		{
			//One more level
			++pos;
			
			//We make its node
			aux.lvl = pos;
			aux.names = makeNames(line);
			
			//Put it into the list
			list.push_back(aux);
		}
		
		void makeOrdered()
		{
			bool madeAny = true;										//If any new level was created in iteration
			int lvl = 0;
			vector<string> alreadyUsed;
			
			
			
			//Create first level: Erdos
			aux.lvl = 0;
			aux.names.clear();
			aux.names.push_back("Erdos, P.");
			alreadyUsed.push_back("Erdos, P.");
			orderedList.push_back(aux);
			aux.names.clear();
			lvl++;

				/*for(unsigned int i = 0; i<orderedList.size(); ++i)
				{
					cout << "Level " << orderedList[i].lvl << ":" << endl;
					for(unsigned int j = 0; j<orderedList[i].names.size(); ++j)
						cout << "\t" << orderedList[i].names[j] << endl;
				}*/

			
			//Create next level from previous level, until no level is made
			while(madeAny)
			{
				aux.lvl = lvl;
				madeAny = false;										//We assume that no levels were made, until we make them
				
				//For each name on previous level
				for(unsigned int i = 0; i<orderedList[lvl-1].names.size(); ++i)
				{
					//Look for it in the big list, in each level
					for(unsigned int j = 0; j<list.size(); ++j)
						for(unsigned int k = 0; k<list[j].names.size(); ++k)
						{
							//If we find a match
							if(orderedList[lvl-1].names[i].compare(list[j].names[k]) == 0)
							{
								//cout << orderedList[lvl-1].names[i] << " is equal to " << list[j].names[k] << endl;
									madeAny= makeLevel(alreadyUsed, aux, list[j].names);
									k = list[j].names.size(); //Because we don't need to look further in that level
							}
						}					
				}
				
				//If we've made a new level, we insert it into the list
				if(!aux.names.empty())
				{
					//cout << "Inserting lvl " << aux.lvl << " first name: " << aux.names[0] << endl;
					orderedList.push_back(aux);
					aux.names.clear();
				}
				else 
				{
					//cout << "break" << endl;
					break;
				}
				++lvl;
			}
		}
		
		bool hasErdos()
		{
			for(unsigned int i = 0; i<list.size(); ++i)
				for(unsigned int j = 0; j<list[i].names.size(); ++j)
					if(list[i].names[j].compare("Erdos, P."))
						return true;
		
			return false;
		}
		
		void find(string person)
		{
			for(unsigned int i = 0; i<orderedList.size(); ++i)
				for(unsigned int j = 0; j<orderedList[i].names.size(); ++j)
					if(person.compare(orderedList[i].names[j])==0)
					{
						cout << person << " " << i << endl;
						return;
					}
			cout << person << " " << "infinity" << endl;
		}
		
		void clear()
		{
			pos = 0;
			list.clear();
			orderedList.clear();
			aux.lvl = 0;
			aux.names.clear();			
		}
};


int main()
{	
	int scenarios = 0, levels = 0, guys = 0;	//The number of each kind
	string line;								//Will process each line
	vector<string> peoplez;						//The people whose level we must show
	
	firstList myList;							//Matrix that will contain the names and initial groups
	
	cin >> scenarios;							//Get the number of scenarios
	for(int x = 0; x<scenarios; ++x)			//Process each scenario
	{
		levels = 0;
		guys = 0;
		line.clear();
		peoplez.clear();
		myList.clear();
		
		cin >> levels >> guys;					//Get the number of levels and people
		getline(cin, line);						//The previous cin does not get the end of line, so we do so here
		
		for(int y = 0; y<levels; ++y)			//We read the groups, insert them into the table
		{
			getline(cin, line);
			myList.insertLine(line);
		}
		
		for(int y = 0; y<guys; ++y)				//We read the people, insert them into the vector
		{
			getline(cin, line);
			peoplez.push_back(line);
		}
		
		/*DEBUG: Show the made levels amd their content
		for(int y = 0; y<levels; ++y)
		{
			cout << "Level: " << myList.list[y].lvl << endl;
			for(int i = 0; i<myList.list[y].names.size(); ++i)
				cout << "\t" << myList.list[y].names[i] << endl;
		}*/
		
		if(myList.hasErdos())
		{
			myList.makeOrdered();
			/*for(unsigned int i = 0; i<myList.orderedList.size(); ++i)
			{
				cout << "Level " << myList.orderedList[i].lvl << ":" << endl;
				for(unsigned int j = 0; j<myList.orderedList[i].names.size(); ++j)
					cout << "\t" << myList.orderedList[i].names[j] << endl;
			}*/
			cout << "Scenario " << (x+1) << endl;
			for(int i = 0; i<guys; ++i)
				myList.find(peoplez[i]);
		}
		else
		{
			cout << "Scenario " << (x+1) << endl;
				for(int i = 0; i<guys; ++i)
					cout << peoplez[i] << " " << "infinity" << endl;
		}
		
	}
	
	return 0;
}
