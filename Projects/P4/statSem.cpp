//
// Created by crbaniak on 5/20/19.
//

#include "statSem.h"

#include "scanner.h"

//
// Created by crbaniak on 5/17/19.
//

#include "statSem.h"

#include <vector>
#include <algorithm>

string holder;

bool hasDuplicates(const std::vector<string>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[i] == arr[j]) {
                holder = arr[i];
                return true;
            }
        }
    }
    return false;
}


void statSem(){

    vector<string> varNames;
    vector<string> usedVarNames;

    //gets variable name
    for(int ii=0; ii < 256;ii++){
        if(finalTokenSet[ii].tokenID == "INTTK"){
            int jj = ii;
            jj++;
            varNames.push_back(finalTokenSet[jj].tokenLiteral);
        } else if(finalTokenSet[ii].tokenID == "OutputTK" ||
                  finalTokenSet[ii].tokenID == "ReadTK"){
            int kk = ii;
            kk += 2;

            if(finalTokenSet[kk].tokenID == "IDTK"){

                if (find(varNames.begin(), varNames.end(), finalTokenSet[kk].tokenLiteral) == varNames.end()) {
                    cout << "ERROR: Variable " << finalTokenSet[kk].tokenLiteral <<
                         " is used before declaration" << endl;
                    return;
                }
            }
        } else if (finalTokenSet[ii].tokenID == "IFFTK" ||
                   finalTokenSet[ii].tokenID == "LoopTK"){

            int lookahead = ii;
            lookahead += 2;

            while(finalTokenSet[lookahead].tokenID != "SYMTK]"){

                lookahead++;

                if(finalTokenSet[lookahead].tokenID == "IDTK"){

                    if (find(varNames.begin(), varNames.end(), finalTokenSet[lookahead].tokenLiteral) == varNames.end()) {
                        cout << "ERROR: Variable " << finalTokenSet[lookahead].tokenLiteral <<
                             " is used before declaration" << endl;
                        return;
                    }
                }
            }
       }
    }



    // removes duplicates
//    sort(varNames.begin(), varNames.end());
//    varNames.erase(unique(varNames.begin(), varNames.end()), varNames.end());

    //checks for duplicates
    if(hasDuplicates(varNames)){
        cout << "ERROR: Variable " << holder << " declared more than once!" << endl;
        return;
    }

    //all good
    cout << "Static Semantics are fine." << endl;
}

