//=============================================================================//
//  ALOE - Computes endemicity statistics from taxon-area NEXUS data matrices  //
//                    Copyright 2006-2024 Mauro J. Cavalcanti                  //
//                          maurobio@gmail.com                                 //
//                                                                             //
//      This program is free software: you can redistribute it and/or modify   //
//      it under the terms of the GNU General Public License as published by   //
//      the Free Software Foundation, either version 3 of the License, or      //
//      (at your option) any later version.                                    //
//                                                                             //
//      This program is distributed in the hope that it will be useful,        //
//      but WITHOUT ANY WARRANTY; without even the implied warranty of         //
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//      GNU General Public License for more details.                           //
//                                                                             //
//      You should have received a copy of the GNU General Public License      //
//      along with this program. If not, see <http://www.gnu.org/licenses/>.   //
//                                                                             //
//   Requirements:                                                             //
//      GNU g++ compiler v3.4.5                                                //
//      Nexus Class Library (NCL) by Paul Lewis v2.0                           //
//      available from http://hydrodictyon.eeb.uconn.edu/ncl/                  //
//                                                                             //
//  REVISION HISTORY:                                                          //
//      Version 1.0, 9th Apr 2006 - Initial version                            //
//      Version 1.1, 3nd Jan 2014 - First public release                       //
//      Version 1.2, 1st Dec 2024 - Second public release                      //
//=============================================================================//

#include <iostream>
#include <string>
#include <ctime>
#include <ncl.h>

using namespace std;

// --- Begin NCL stuff
class Token : public NxsToken
	{
	public:
		Token(istream &is, ostream &os) : out(os), NxsToken(is) {}
		void OutputComment(const NxsString &msg) {
			cout << msg << endl;
			out << msg << endl;
			}
	private:
		ostream &out;
	};

class Reader : public NxsReader
	{
	public:
		ifstream inf;
		ofstream outf;

		Reader(char *infname, char *outfname) : NxsReader()
			{
			inf.open(infname, ios::binary);
            cout << "Opening input data file " << infname << endl;
			outf.open(outfname);
			}

		~Reader()
			{
			inf.close();
			outf.close();
			}

	void ExecuteStarting()
        {
        cout << "Reading data file..." << endl;
        }
            
	void ExecuteStopping() {}

	bool EnteringBlock(NxsString blockName)
		{
		cout << "Reading \"" << blockName << "\" block..." << endl;
		return true;
		}

    void ExitingBlock( NxsString blockName ) 
        {
        cout << "Finished with " << blockName << " block." << endl;
		}

	void SkippingBlock(NxsString blockName)
		{
		cout << "Skipping unknown block (" << blockName << ")..." << endl;
		}

	void SkippingDisabledBlock(NxsString blockName)
        {
        cout << "Skipping disabled block (" << blockName << ")..." << endl;
        }

	void OutputComment(const NxsString &msg)
		{
		outf << msg << endl;
		}

	void NexusError(NxsString msg, file_pos pos, unsigned line, unsigned col)
		{
		cerr << endl;
		cerr << "Error found at line " << line;
		cerr << ", column " << col;
		cerr << " (file position " << pos << "):" << endl;
		cerr << msg << endl;

		outf << endl;
		outf << "Error found at line " << line;
		outf << ", column " << col;
		outf << " (file position " << pos << "):" << endl;
		outf << msg << endl;
		exit(0);
		}
};
// --- End NCL stuff

float percent(int val1, int val2)
{
    float ret_val;  
	if (val2 == 0)
		ret_val = 0.0;
	else
		ret_val = (float(val1) / float(val2)) * 100.00;
	return(ret_val);
}

int main(int argc, char* argv[])
{
        NxsTaxaBlock* taxa = new NxsTaxaBlock();
        NxsAssumptionsBlock* assumptions = new NxsAssumptionsBlock (taxa);
        NxsCharactersBlock* characters = new NxsCharactersBlock (taxa, assumptions);
        NxsDataBlock* data = new NxsDataBlock (taxa, assumptions);
        NxsTreesBlock* trees = new NxsTreesBlock(taxa);
        
        cout << "****************************************" << endl;
        cout << " * AnaLysis Of Endemicity program v1.1 *" << endl;
        cout << "****************************************" << endl;
        cout << "(c) 2006-2024 Mauro J. Cavalcanti" << endl;
        cout << "Ecoinformatics Studio, Rio de Janeiro, Brazil" << endl;
        cout << "E-mail: maurobio@gmail.com" << endl;

        // Get input file name
        char infile[80];
        cout << "\nEnter file name: ";
        cin.getline(infile, 80); 
		int ext = '.';
		const char* extension = NULL;
		extension = strrchr(infile, ext);
		if((extension == NULL) || (strcmp(extension, ".nex")) !=0) {
			cout << "Invalid extension encountered!\n";
			return 1;
		}
        int outno;
        cout << "\nEnter outgroup number (0 for none): ";
        cin >> outno;
        cout << endl;
        
        // Open input and output (results) files
        Reader nexus (infile, "Aloe.txt");
        nexus.Add (taxa);
        nexus.Add (assumptions);
        nexus.Add (characters);
        nexus.Add (data);
        nexus.Add (trees);
        Token token (nexus.inf, nexus.outf);
        nexus.Execute (token);

        // Get number of characters (species) and taxa (areas) from the input file
        int ntax, nchar;
        if (!characters->IsEmpty()) {
           if (outno > 0) {
             characters->DeleteTaxon(outno);
             ntax = characters->GetNumActiveTaxa();
           } 
           else 
             ntax = characters->GetNTax();
           nchar = characters->GetNChar();
           }
        else if (!data->IsEmpty()) {
           if (outno > 0) {
             data->DeleteTaxon(outno);
             ntax = data->GetNumActiveTaxa();
           } 
           else
             ntax = data->GetNTax();
           nchar = data->GetNChar();
        }

        // Store data matrix
        NxsDiscreteMatrix* matrix = new NxsDiscreteMatrix (ntax, nchar);
        if (!matrix) {
           cout << "Error storing data matrix! Execution terminated." << endl;
           return(1);
        }   

        unsigned char dataMatrix [ntax][nchar];
        for (int i = 0; i < ntax; i++) {
            for (int j = 0; j < nchar; j++) {
               if (!characters->IsEmpty()) {
                  if (!characters->IsMissingState(i, j))
                    dataMatrix[i][j] = characters->GetState(i, j, 0);
                  else
                    dataMatrix[i][j] = characters->GetMissingSymbol();
               }
               else if (!data->IsEmpty()) {
                  if (!data->IsMissingState(i, j))
                    dataMatrix[i][j] = data->GetState(i, j, 0);
                  else
                    dataMatrix[i][j] = data->GetMissingSymbol();
               }
            }
        }
        cout << "Data matrix stored in memory." << endl;
        
        // --- Write data matrix to csv file
        //ofstream csvf;
        //csvf.open("aloe.csv");
        //csvf << taxa->GetTaxonLabel(0).c_str();
        //for (int k = 1; k < ntax; k++) {
        //  csvf << ";" << taxa->GetTaxonLabel(k).c_str();
        //}
        //csvf << endl;
        //for (int j = 0; j < nchar; j++) {
        //  csvf << characters->GetCharLabel(j).c_str();
        //  for (int i = 0; i < ntax; i++) {
        //    csvf << ";" << dataMatrix[i][j];
        //  }
        //  csvf << endl;
        //}    
        //csvf.close();

        cout.setf(ios::left);
        nexus.outf.setf(ios::left);
        nexus.outf << "AnaLysis Of Endemicity program v1.2" << endl;
        
        time_t now = time(0);
        char* dt = ctime(&now);
        nexus.outf << "Date and time of analysis - " << dt;
        nexus.outf << "Data file - " << infile << endl << endl;

        // Compute area statistics
        cout << "Area statistics" << endl << endl;
        nexus.outf << "Area statistics" << endl << endl;
        for (int i = 0; i < ntax; i++) {
          int n = 0;
          for (int j = 0; j < nchar; j++) {
            if (dataMatrix[i][j] == '1') n++;
          }
          cout << setw(40) << taxa->GetTaxonLabel(i).c_str() << " " << setw(10) << n << " taxa" << endl;
          nexus.outf << setw(40) << taxa->GetTaxonLabel(i).c_str() << " " << setw(10) << n << " taxa" << endl;
        }
        cout << string(56, '-') << endl;
        nexus.outf << string(56, '-') << endl;
        cout << "Total areas = " << ntax << endl;
        nexus.outf << "Total areas = " << ntax << endl;
        cout << string(56, '-') << endl;
        nexus.outf << string(56, '-') << endl << endl;
     
        // Compute species statistics
        cout << "Species statistics" << endl << endl;
        nexus.outf << "Species statistics" << endl << endl;
        string status;
        int total = 0;
        for (int j = 0; j < nchar; j++) {
          int freq = 0;
          for (int i = 0; i < ntax; i++) {
            if (dataMatrix[i][j] == '1') freq++;
          }     
          
          switch (freq) {
            case 0:
              status = "Absent";
              break;
            case 1:
              total++;
              status = "Endemic";
              break;
            default:
              status = "Widespread";
              break;  
          }     
          
          if (!characters->IsEmpty()) {
            cout << setw(40) << characters->GetCharLabel(j).c_str() << setw(10) << freq << setw(10) << status << endl;
            nexus.outf << setw(40) << characters->GetCharLabel(j).c_str() << setw(10) << freq << setw(10) << status << endl;
          }  
          else if (!data->IsEmpty()) {
            cout << setw(40) << data->GetCharLabel(j).c_str() << setw(10) << freq << setw(10) << status << endl;
            nexus.outf << setw(40) << data->GetCharLabel(j).c_str() << setw(10) << freq << setw(10) << status << endl;
          }  
        }    
        
        cout << string(60, '-') << endl;
        nexus.outf << string(60, '-') << endl;
        cout << "Total taxa = " << nchar << endl;
        cout << "Total widespread taxa = " << (nchar - total) << endl;
        cout << "Total endemics = " << total << endl;
        nexus.outf << "Total taxa = " << nchar << endl;
        nexus.outf << "Total widespread taxa = " << (nchar - total) << endl;
        nexus.outf << "Total endemics = " << total << endl;
        cout << string(60, '-') << endl << endl;
        nexus.outf << string(60, '-') << endl << endl;
        
        // Compute occurrence statistics
        cout << "Ocurrence statistics" << endl;
        nexus.outf << "Ocurrence statistics" << endl;
        int one = 0, two = 0, three = 0, four = 0, five = 0;
        for (int j = 0; j < nchar; j++) {
          int freq = 0;
          for (int i = 0; i < ntax; i++) {
            if (dataMatrix[i][j] == '1') freq++;
          }     
          
          switch (freq) {
              case 1:
                one++;
                break;
              case 2:
                two++;
                break;
              case 3:
                three++;
                break;
              case 4:
                four++;
                break;
              case 5:
                five++;
                break;        
              default:
                five++;
                break;  
          }
        }
          
        cout << endl;
        nexus.outf << endl;  
        cout << "Species occurring in:" << endl;
        nexus.outf << "Species occurring in..." << endl;
        cout << setw(40) << "   One area " << setw(10) << one << "(" << setprecision(3) << percent(one, nchar) << "%)" << endl;
        cout << setw(40) << "   Two areas " << setw(10) << two << "(" << setprecision(3) << percent(two, nchar) << "%)" << endl;
        cout << setw(40) << "   Three areas " << setw(10) << three << "(" << setprecision(3) << percent(three, nchar) << "%)" << endl;
        cout << setw(40) << "   Four areas " << setw(10) << four << "(" << setprecision(3) << percent(four, nchar) << "%)" << endl;
        cout << setw(40) << "   Five or more areas " << setw(10) << five << "(" << setprecision(3) << percent(five, nchar) << "%)" << endl;
        nexus.outf << setw(40) << "   One area " << setw(10) << one << "(" << setprecision(3) << percent(one, nchar) << "%)" << endl;
        nexus.outf << setw(40) << "   Two areas " << setw(10) << two << "(" << setprecision(3) << percent(two, nchar) << "%)" << endl;
        nexus.outf << setw(40) << "   Three areas " << setw(10) << three << "(" << setprecision(3) << percent(three, nchar) << "%)" << endl;
        nexus.outf << setw(40) << "   Four areas " << setw(10) << four << "(" << setprecision(3) << percent(four, nchar) << "%)" << endl;
        nexus.outf << setw(40) << "   Five or more areas " << setw(10) << five << "(" << setprecision(3) << percent(five, nchar) << "%)" <<endl;
        
        //cout << "\nPress the <ENTER> key to finish...";
        //cin.get();
        return 0;
}
