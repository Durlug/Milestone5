//Milestone 4
//OnShelf.h
//Shaun Richardson
//110392156
//srichardson6@myseneca.ca


#ifndef ICT_ONSHELF_H__
#define ICT_ONSHELF_H__

#include "Good.h"
#include "Error.h"
namespace ict 
{
   class OnShelf : public Good
   {
   private:
	   char recTag_;
   protected:
	   Error err_;
   public:
	   OnShelf(char filetag = 'O');
	   virtual std::fstream& store(std::fstream& file, bool addNewLine = true)const;
	   std::fstream& load(std::fstream& file);
	   std::ostream& display(std::ostream& os, bool linear) const;
	   std::istream& conInput(std::istream& istr);
   };
}
#endif