//###############################################################################################################################################
//
//	Meta and Builder Object Network V2.0 for GME
//	BON2Component.cpp
//
//###############################################################################################################################################

/*
	Copyright (c) Vanderbilt University, 2000-2004
	ALL RIGHTS RESERVED

	Vanderbilt University disclaims all warranties with regard to this
	software, including all implied warranties of merchantability
	and fitness.  In no event shall Vanderbilt University be liable for
	any special, indirect or consequential damages or any damages
	whatsoever resulting from loss of use, data or profits, whether
	in an action of contract, negligence or other tortious action,
	arising out of or in connection with the use or performance of
	this software.
*/

#include "stdafx.h"
#include <Console.h>
#include "BON2Component.h"

#include <sstream>
#include  <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <cstddef>
namespace BON
{

//###############################################################################################################################################
//
// 	C L A S S : BON::Component
//
//###############################################################################################################################################

Component::Component()
	: m_bIsInteractive( false )
{
}

Component::~Component()
{
	if ( m_project ) {
		m_project->finalizeObjects();
		finalize( m_project );
		m_project = NULL;
	}
}

// ====================================================
// This method is called after all the generic initialization is done
// This should be empty unless application-specific initialization is needed

void Component::initialize( Project& project )
{
	// ======================
	// Insert application specific code here
#ifdef GME_ADDON
	project->setAutoCommit( false);
#endif
}

// ====================================================
// This method is called before the whole BON2 project released and disposed
// This should be empty unless application-specific finalization is needed

void Component::finalize( Project& project )
{
	// ======================
	// Insert application specific code here
}

// ====================================================
// This is the obsolete component interface
// This present implementation either tries to call InvokeEx, or does nothing except of a notification

void Component::invoke( Project& project, const std::set<FCO>& setModels, long lParam )
{
	#ifdef SUPPORT_OLD_INVOKE
		Object focus;
		invokeEx( project, focus, setModels, lParam );
	#else
		if ( m_bIsInteractive )
			AfxMessageBox(_T("This BON2 Component does not support the obsolete invoke mechanism!"));
	#endif
}

// ====================================================
// This is the main component method for Interpereters and Plugins.
// May also be used in case of invokeable Add-Ons

void Component::invokeEx( Project& project, FCO& currentFCO, const std::set<FCO>& setSelectedFCOs, long lParam )
{
#ifdef GME_ADDON
	project->setAutoCommit( false);
#endif
	using namespace GMEConsole;
	Console::Out::WriteLine(_T("Interpreter started..."));
	// ======================
	// TODO: Insert application specific code here


	BON::Folder rf = project->getRootFolder( );

if( rf )

{

std::set<Model> models = rf->getChildModels( );

std::stringstream stream;

 stream << "We have this many models:" << models.size( );

Console::Out::WriteLine(CString(stream.str( ).c_str( )) );

// let's look through each model and print it out to a file

std::ofstream outfile;

 outfile.open("test.cpp");

if( outfile.is_open( ) )

{
	//outfile << "My name is NishanthP"<<std::endl;
 Console::Out::WriteLine("We opened the file...");

for( std::set<Model>::iterator it = models.begin( ); it != models.end( ); it++ )

{

Model model = *it;

 outfile << "void " << model->getName( ) << "( ";

// I need to go through all the input ports

// NOTE: We called these sources, not inputs---that was the source (heh heh)

// of the runtime errors

 std::set<BON::FCO> sources = model->getChildFCOsAs("Source");

// stream.flush( );

 stream << "We have this many sources:" << sources.size( );

Console::Out::WriteLine(CString(stream.str( ).c_str( ) ) );

for( std::set<BON::FCO>::iterator it2=sources.begin( ); it2!= sources.end( ); it2++ )

{

 outfile << " int *" << (*it2)->getName( ) << ",";

}

// now, do the sinks

 std::set<BON::FCO> sinks = model->getChildFCOsAs("Sink"); 

int i=sinks.size( );

for( std::set<BON::FCO>::iterator it3=sinks.begin( ); it3!= sinks.end( ); it3++, i-- )

{

 outfile << " int *" << (*it3)->getName( );

if( i > 1 )

{

 outfile << ",";

}

}

 outfile << ")" << std::endl << "{" << std::endl;

// placeholder

// outfile << "// go ahead and process outputs now " << std::endl;


 //-----------------------------------Nishanth Prakash---------------------------------//

 	 
std::string array[4]={"And","Not","Nor","Nand"};			// This vector consists of  array of Atoms in the model
										 


 for(int i =0;i<4;i++)
{
newMethod(array[i],model);									// this method is used to traverse through all the Atoms in the model except the Source and the Sink
}

 for(int i=0;i<array_Nodes.size();i++)
 {
	 if(array_Nodes[i].Name.empty())
	 {
		 continue;
	 
	 }
	 outfile<<"int"<<"*"<<array_Nodes[i].output<<"="<<"new int()"<<";"<<std::endl;		//Initialize all the variables declared.
 }

std::vector<std::vector<bool>> adj_matrix(4, std::vector<bool>(4,0));	/*A matrix is created of the same size of the array. This is used to see the dependencies between the
																			 input of one Atom and the output of another Atom*/	
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(array_Nodes[i].output==array_Nodes[j].input1 || array_Nodes[i].Name==array_Nodes[j].input2)
			{
			
				adj_matrix[i][j]=1;						//Stores a 1 if there are dependencies 
				
			}
			else
				adj_matrix[i][j]=0;						// Stores a 0 if there are no dependencies


		}
	
	}

	static int flagArray=0;						//flagArray is raised to 1 when it encounters a 1 while traversing the matrix
	for (int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			int temp=adj_matrix[i][j];
			if(temp==1)
			{
				flagArray = 1;
				break;
			}
		}
		
		if (flagArray==0)											// If the flagArray is not raised, then there are no dependencies, thus will continue all the Equations
		{
		if(array_Nodes[i].Name=="And")
		{
			outfile <<"*"<<array_Nodes[i].output<<"="<<"("<<"*"<<array_Nodes[i].input1 <<"&"<<"*"<<array_Nodes[i].input2<<")"<<";"<<std::endl; //Used to print the appropriate AND Equations

		}
		 
		else if(array_Nodes[i].Name=="Nor")
		{
			
			outfile <<"*"<<array_Nodes[i].output<<"="<<"!("<<"*"<<array_Nodes[i].input1 <<"||"<<"*"<<array_Nodes[i].input2<<")"<<";"<<std::endl;//Used to print the appropriate NOR Equations
		}

		else if(array_Nodes[i].Name=="Not")
		{
			outfile <<"*"<<array_Nodes[i].output<<"="<<"!"<<"("<<"*"<<array_Nodes[i].input1<<")"<<";"<<std::endl;//Used to print the appropriate NOT Equations
		}
		else if(array_Nodes[i].Name=="Nand")
		{
			outfile <<"*"<<array_Nodes[i].output<<"="<<"!("<<"*"<<array_Nodes[i].input1<<"&"<<"*"<<array_Nodes[i].input2<<")"<<";"<<std::endl;//Used to print the appropriate NAND Equations
		}

		}
		else
		{
			flagArray=0;				// if a dependency is found, do not print the equation, make flagArray=0 and continue to the next equation (Atom)
			continue;
		}
		
	
	}


}

for( std::set<BON::FCO>::iterator it3=sinks.begin( ); it3!= sinks.end( ); it3++)

{

	std::set<BON::Connection>link = (*it3)->getConnLinks();				//All the links connected to the Sink is iterated and thier source is found out and printed.

	for(std::set<BON::Connection>::iterator it5 = link.begin(); it5 != link.end(); it5++)
	{
		BON::ConnectionEnd obj;
		if((*it5)->getDst()==(*it3))
		{
			
			obj= (*it5)->getSrc();										//To get the source of the connection only if the connection destination is the atom itself

			if (BON::FCO (obj))											
			{
				BON::FCO otherFCO(obj);
				outfile <<"*"<<(*it3)->getName()<<"="<<"*"<< otherFCO->getName()<<";"<<std::endl;
			}
			
		}
	}

}

 outfile << "}" << std::endl << std::endl;

//---------------------------------------NishanthPrakash----------------------------------------------//



 

}

outfile.close( );

}

}




















	Console::Out::WriteLine(_T("Interpreter completed..."));
}


//--------------------------------------------------------------NishanthPrakash-----------------------------------//
/* This method is mainly used to iterate over each atom in the model, and iterate over each link of the each atom*/
void Component:: newMethod (std::string str, Model &model)		
	{
		using namespace GMEConsole;
		std::stringstream stream1;
	std::set<BON::FCO> source = model->getChildFCOsAs(str);

	static int index=0;
	static int flag=0;
	for(std::set<BON::FCO>::iterator it = source.begin(); it != source.end(); it++) //Iterate over all the Atoms in the model
	{
	std:: stringstream stream1;
		
	std::set<BON::Connection>links = (*it)->getConnLinks();			//Used to get all the links the Atom is connected to.
	
	flag=0;
	for(std::set<BON::Connection>::iterator it1 = links.begin(); it1 != links.end(); it1++) //iterate over all the links of one Atom
	{
		ConnectionEnd obj;
		if((*it1)->getDst()==(*it))
		{
			obj= (*it1)->getSrc();

			if (BON::FCO (obj))
			{
				BON::FCO otherFCO(obj);
				array_Nodes.push_back(Node());						// This vector method will create a structre for each atom and store the structure in the vector 
				
				if(flag==0)											//flag is used to prevent over riding of names in each structure
				{

				array_Nodes[index].input1 = otherFCO->getName();
				flag=1;
				}
																
				else  
				{
					
				array_Nodes[index].input2 = otherFCO->getName();
				
				}

				array_Nodes[index].Name = (*it)->getObjectMeta().name();
				array_Nodes[index].output = (*it)->getName();
			}
			
		
		}
		
	}
		index=index+1;
	}

	}
//---------------------------------------------NishanthPrakash--------------------------------------------//








// ====================================================
// GME currently does not use this function
// You only need to implement it if other invokation mechanisms are used

void Component::objectInvokeEx( Project& project, Object& currentObject, const std::set<Object>& setSelectedObjects, long lParam )
	{
		if ( m_bIsInteractive )
			AfxMessageBox(_T("This BON2 Component does not support objectInvokeEx method!"));
	}

// ====================================================
// Implement application specific parameter-mechanism in these functions

Util::Variant Component::getParameter( const std::string& strName )
{
	// ======================
	// Insert application specific code here

	return Util::Variant();
}

void Component::setParameter( const std::string& strName, const Util::Variant& varValue )
{
	// ======================
	// Insert application specific code here
}

#ifdef GME_ADDON

// ====================================================
// If the component is an Add-On, then this method is called for every Global Event

void Component::globalEventPerformed( globalevent_enum event )
{
	// ======================
	// Insert application specific code here
}

// ====================================================
// If the component is an Add-On, then this method is called for every Object Event

void Component::objectEventPerformed( Object& object, unsigned long event, VARIANT v )
{
	// ======================
	// Insert application specific code here
}

#endif // GME_ADDON

}; // namespace BON

