//Milestone 5
//WPlanner.cpp
//Shaun Richardson
//110392156
//srichardson6@myseneca.ca



#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>
#include <string>
#include "WPlanner.h"
#include "Good.h"
#include "OnShelf.h"
#include "CustomMade.h"

using namespace std;
namespace ict {

   WPlanner::WPlanner(const char* filename) 
   {
	   if (filename)
	   {
		   strncpy(filename_, filename, 256);
		   if (strlen(filename) >= 256)
		   {
			   filename_[256 - 1] = 0;
		   }
		   for (int i = 0; i < MAX_NO_RECS; i++)
		   {
			   items_[i] = nullptr;             //setting all pointers in the Good objects array (items_) to null 
		   }

		   noOfItems_ = 0;
		   loadRecs();
	   }
   }
   void WPlanner::saveRecs() 
   {
	   datafile_.open(filename_, ios::out);

	   for (int i = 0; i < noOfItems_; i++)
	   {
		   items_[i]->store(datafile_, true);
	   }
	   datafile_.clear();
	   datafile_.close();

   }
   void WPlanner::loadRecs()
   {
	   noOfItems_ = 0;
	   char c;                              //ID character
	  
	   datafile_.open(filename_, ios::in);

	   if (datafile_)
	   {
		   while (!datafile_.eof())         //Looping through the file until reading is complete
		   {
			   
			   if (datafile_ >> c)
			   {
				   if (c == 'C')           //if the value of c is 'C' object is a CustomMade object
				   {
					   items_[noOfItems_] = new CustomMade;
				   }
				   else if (c == 'O')     //if the value of c is O object is an ObShelf object
				   {
					   items_[noOfItems_] = new OnShelf;
				   }
				   datafile_.ignore();
				   items_[noOfItems_]->load(datafile_);       //using the load function to load the data into the datafile
				   noOfItems_++;                              //increasing noOfItems by one for each loop
			   }
		   }

	   }
	   else       //if the file fails 
	   {
		   datafile_.clear();                     //Clear failure
		   datafile_.close();                     //Close File
		   datafile_.open(filename_, ios::out);   //Create file
		   datafile_.close();                     //Close file
	   }
	   datafile_.close();
	}

   void WPlanner::getSku(char* sku) 
   {
	   cout << "Please enter the SKU: ";
	   cin >> sku;
	   if (cin.fail())
	   {
		   cin.clear();
		   cin.ignore(INT_MAX, '\n');
	   }



   }

   void WPlanner::deleteItem() 
   {
      cout << "Not implemented!" << endl << endl;
   }

   void WPlanner::updateQty() 
   {
	   char* sku = new char[MAX_SKU_LEN + 1];  // Have to dynamically allocated memory for Sku or else error occurs
	   int a, qty, amount, extra;  //Variables: holding function, quantity entered, amount required, extra quantity
	   Good* good;  //Create temporary good object

	   getSku(sku);    //Using getSku function to retrieve the Sku varilable
	   a = SearchItems(sku);   //Variable to hold the output of SearchItems(either index number or -1)

	   if (a >= 0)               //If SearchItems set to variable a is anything except -1
	   {
		   good = items_[a];
		   good->display(cout, false); //Display good in non linear format
		   cout << endl;  //Skipping line
		   cout << "Please enter the number of purchased goods: ";
		   cin >> qty;
		   if (cin.fail())   //If function cannot read integer
		   {
			   cout << "Invalid Quantity value!" << endl;
		   }
		   else
		   {
			   amount = (good->qtyNeeded() - good->quantity()); //Amount needed to match the quantity needed
			   if (qty <= amount)   //If quantity is less or equal to quantity needed
			   {
				   *good += qty;    //Add the qty entered to the goods quantity
			   }
			   else
			   {
				   *good += amount;   //Adds the amount needed to the goods quantity
				   extra = qty - amount;   //Variable equalling the extra amount of good entered
				   cout << "Too many purchased, only " << amount << " needed, please return the extra " << extra << ".";
			   }
			   saveRecs();
			   cout << endl << "Updated!" << endl << endl;
			   cin.clear();  //Clearing buffer
			   cin.ignore(INT_MAX, '\n'); //Clearing buffer
		   }

	   }
	   else
	   {
		   cout << "Not found!" << endl;
	   }


	}

   void WPlanner::listItems()const 
   {
	   double total = 0;         //Total variable to hold total cost of the wedding

      cout << " Row | SKU | Good Name          | Cost  |Tax| QTY|Need| Delivery" << endl
         << "-----|-----|--------------------|-------|---|----|----|----------" << endl;

	  for (int i = 0; i < noOfItems_; i++)
	  {
		  cout << right << setw(4) << (i + 1) << " | "; 
		  items_[i]->display(cout, true);   //using good display function 
		  total += *items_[i];   //Using overloaded += to add total goods together
	  }


      cout << "-----+-----+--------------------+-------+---+----+----+----------" << endl;
	  cout << "Total cost of the Wedding: $" << setprecision(2) << fixed << showpoint << total << endl << endl;
	}

   int WPlanner::SearchItems(const char* sku)const 
   {
	   int i;
	   for (i = 0; i < noOfItems_; i++)
	   {
		   if (*items_[i] == sku)
		   {
			   return i;
		   }
		   else
			   return -1;
	   }
	}

   void WPlanner::addItem(bool isCustomMade) 
   {
	   if (isCustomMade)
	   {
		   CustomMade temp;                              //Create CustomMade object
		   temp.conInput(cin);                          //Using conInput function to populate object
		   datafile_.open(filename_, ios::out);         
		   for (int i = 0; i < noOfItems_; i++)
		   {
			   items_[i]->store(datafile_, true);  //Using store function to store into file
		   }
		   temp.store(datafile_);                   //Storing data 
		   datafile_.close();

		   cout << endl << "Good Added!" << endl << endl;
	   }
	   else
	   {
		   OnShelf temp;              //Create OnShelf object
		   temp.conInput(cin);        //using conInput function to populate Object
		   datafile_.open(filename_, ios::out);
		   for (int i = 0; i < noOfItems_; i++)
		   {
			   items_[i]->store(datafile_, true);
		   }
		   temp.store(datafile_);  //Using store function to store into file
		   datafile_.close();

		   cout << endl << "Good Added!" << endl << endl;
	   }
   }

   int WPlanner::menu() {
      int selection;

	  cout << "Wedding Planner Management Program" << endl
		  << "1 - List goods" << endl
		  << "2 - Add On Shelf Good" << endl
		  << "3 - Add Custom-Made Good" << endl
		  << "4 - Update Good quantity" << endl
		  << "5 - Delete" << endl
		  << "0 - Exit program" << endl
		  << "> ";
	  cin >> selection;

	  if (cin.fail() || selection > 5)   //If input fails, or user input is invalid (needs to be 0-4)
	  {
		  cin.clear();       //Clear buffer
		  cin.ignore(INT_MAX, '\n'); //Clear buffer
		  selection = -1;     //Selection set to -1
	  }
	return selection;
   }


   int WPlanner::run() 
   {
      bool done = false;
      while (!done) {
         switch (menu()) {
         case 1:
			 listItems();
            break;
         case 2:
			 addItem(false);   //Adding On Shelf Item
			 loadRecs();
			 cin.clear();
			 cin.ignore(INT_MAX, '\n');
            break;
         case 3:
			 addItem(true);    //Adding Custom-Made Good
			 loadRecs();
			 cin.clear();
			 cin.ignore(INT_MAX, '\n');
			 break;
         case 4:
			 updateQty();

            break;
         case 5:
			 deleteItem();
            break;
         case 0:
            done = true;
            cout << "Goodbye!!" << endl << endl;
            break;
		 case -1:
            cout << "===Invalid Selection, try again.===" << endl <<endl ;
            break;
         }
      }
      return 0;
   } // WPlanner::run() end
}


/* outputs

Wedding Planner Management Program
1 - List goods
2 - Add On Shelf Good
3 - Add Custom-Made Good
4 - Update Good quantity
5 - Delete
0 - Exit program
>



Not found!

Please enter the number of purchased goods:

Too many purchased, only 5 needed, please return the extra 15.

Updated!

Not implemented!

*/