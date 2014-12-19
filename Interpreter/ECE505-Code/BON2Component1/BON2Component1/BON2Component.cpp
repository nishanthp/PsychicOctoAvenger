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
#include "Plugin.h"
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

stream << "We have this many models:" << models.size( )<<std::endl;

Console::Out::WriteLine(CString(stream.str( ).c_str( )) );

// let's look through each model and print it out to a file

std::ofstream outfile;

 outfile.open("test.cpp");

if( outfile.is_open( ) )

{
	
 Console::Out::WriteLine("We opened the file...");

for( std::set<Model>::iterator it = models.begin( ); it != models.end( ); it++ )

{

Model model = *it;


//--------------------------------------------------------------ECE505 Added by NishanthPrakash--------------------------------------//
std::set<BON::Attribute>input;							//used to get the attributes of the source atom. To parse the string given by the user.
std::string inputString;								//holds the string passed by the user (from the drop down menu) from the GME tool
std::set<BON::FCO> source_dst;
std::string name_Atom;									//holds the destination of the source atom
std::string plugin_Atom;								//used to store the meta model name of those atoms which are the destinations of the switch
std::string dstofSwitch[5];								//contains the destination of the switches

bool exsists = false;									// A flag is raised only if the input given the user matches with one of the destinations of the switch 
std::set<BON::FCO> source;								// A set which consists of a source atom
PluginImpl::CPU_Usage cu;								//object of a class which contains the methods of CPU_Usage  
PluginImpl::Open_Process op;							//object of a class which contains the methods of Open_Process
PluginImpl::Memory_Load ml;								//object of a class which contains the methods of Memory_Load
PluginImpl::Memory_Usage mu;							//object of a class which contains the methods of Memory_Usage 
PluginImpl::Shared_Folders sf;							//object of a class which contains the methods of Shared_Folders 

/**
A runtime exception is thrown only if the source does not exsist and the appropriate error message is displayed on the console of the GME model
**/
try
{
	source = model->getChildFCOsAs("Source");
	if(source.empty())
	{
		throw std::runtime_error("Source must exsist! You cannot select what you want to generate!");
	}
}
catch(std::runtime_error &e)
{
	std::stringstream stream1;
	stream1 << e.what() << std::endl;

	Console::Out::WriteLine(CString(stream1.str( ).c_str( ) ) );

}



std::stringstream stream1;
if(!source.empty())									//check the exsistance of source 
{


	for( std::set<BON::FCO>::iterator it1=source.begin( ); it1!= source.end( ); it1++ )			// will iterate over all the sources. In this case, there is only one source

{
	input= (*it1)->getAttributes();				
	for(std::set<BON::Attribute>::iterator it7=input.begin( ); it7!= input.end( ); it7++)
	{
		inputString = (*it7)->getStringValue();									//takes in the input given in the GME tool.
		
	
	}
	std::set<BON::Connection>links = (*it1)->getConnLinks();
	for(std::set<BON::Connection>::iterator it2 = links.begin(); it2 != links.end(); it2++) //iterate over all the links of one Atom
	{
		ConnectionEnd obj;
		if((*it2)->getSrc()==(*it1))						//will get the source connection links, in this case it would be the switch atom itself
		{
			obj= (*it2)->getDst();							// the destination of those connection links are stored in the obj
	
			if (BON::FCO (obj))
			{
				BON::FCO otherFCO(obj);
				name_Atom = otherFCO->getObjectMeta().name();	// convert obj into First Class Object (FCO)
				
				source_dst.insert(obj);							//source_dst contains all the atoms connected to the switch atom 
			}
			
		
		}


	}


}
	/**
	A runtime exception is thrown only if the destination of the source is not a switch and the appropriate error message is displayed on the console of the GME model
	**/
	try
{
	if(name_Atom!="Switch")											
	{
		throw std::runtime_error("A Switch must exsist!. The interpreter cannot find the path to the class to generate the program");		 
	}																	
}
catch(std::runtime_error& e1)
{
	stream1 << e1.what() << std::endl;

	Console::Out::WriteLine(CString(stream1.str( ).c_str( ) ) );
}

}



int i=0;
if(name_Atom=="Switch")						//name_Atom contains the name of the destinaton atom of the source
{
	//outfile << inputString;
	for( std::set<BON::FCO>::iterator it3=source_dst.begin( ); it3!= source_dst.end( ); it3++ ) //iterate through all the atoms connected to the switch
	{
		std::set<BON::Connection>links = (*it3)->getConnLinks();
	
		for(std::set<BON::Connection>::iterator it4 = links.begin(); it4 != links.end(); it4++) //iterate over all the links of one Atom
		{

			ConnectionEnd obj;
		if((*it4)->getSrc()==(*it3))						//eleimantes those connections whose destinations are not the switch itself
		{
			obj= (*it4)->getDst();	
	
			if (BON::FCO (obj))								// the destinations of the switch is converted to a First Class Object
			{
				BON::FCO otherFCO(obj);
				plugin_Atom = otherFCO->getObjectMeta().name();
				dstofSwitch[i] = plugin_Atom;				// the meta name of each of the atoms (destination of switch) are stored in the array dstofSwitch
				i++;

			}

			
		}
		}
	}

}


for(int i=0;i<4;i++)
{
	if(dstofSwitch[i]==inputString)
	{
		exsists = true;					//boolean value exsists becomes true when the input given the user matches with any of the destination atoms of the switch 
	
	}
}
/*
Only one of the if conditions will satisfy for one execution of the interpreter code
*/

for(int i=0;i<1;i++)
{
	if(name_Atom=="Switch")													//the below code shoud not execute if destination of source is not a switch
	{
	if(exsists)																//exsists flag is raised only if the inputString value matches with the name of the atoms
	{
				if(inputString=="UserProcessCounter")						//UserProcessCounter object sf and its methods are called.
				{
					op.construct(outfile);
					op.failTest(outfile);
					op.executePlugin(outfile);
					op.checkArgs(outfile);
					Console::Out::WriteLine(_T("Interpreter completed Successfully..."));
					break;
				}
				if(inputString=="CPULoadComparison")						//CPULoadComparison object sf and its methods are called.
				{
					cu.construct(outfile);
					cu.failTest(outfile);
					cu.executePlugin(outfile);
					cu.checkArgs(outfile);
					Console::Out::WriteLine(_T("Interpreter completed Successfully..."));
					break;
				}
				if(inputString=="MemoryLoad")								//MemoryLoad object sf and its methods are called.
				{
					ml.construct(outfile);
					ml.failTest(outfile);
					ml.executePlugin(outfile);
					ml.checkArgs(outfile);
					Console::Out::WriteLine(_T("Interpreter completed Successfully..."));
					break;
				}
				
				if(inputString=="Memory_Usage")								//Memory_Usage object sf and its methods are called.
				{
					mu.construct(outfile);
					mu.failTest(outfile);
					mu.executePlugin(outfile);
					mu.checkArgs(outfile);
					Console::Out::WriteLine(_T("Interpreter completed Successfully..."));
					break;
					
				}
				if(inputString=="Shared_Folders")							//Shared_Folders object sf and its methods are called.
				{
					
					sf.construct(outfile);
					sf.failTest(outfile);
					sf.executePlugin(outfile);
					sf.checkArgs(outfile);
					Console::Out::WriteLine(_T("Interpreter completed Successfully..."));
					break;
				}

}
else if (!(exsists))				// This condition is performed to see the exsistance of Atom which has the same name as the class name.
{
		std::stringstream stream2;
		stream2 << "ERROR! The input does not match with any of the present class names!";
		Console::Out::WriteLine(CString(stream2.str( ).c_str( )) );

}

}
}

//--------------------------------------------------ECE505 Added by NishanthPrakash------------------------------------------------//

}

outfile.close( );		//This is to close the output file.

}

}

	
}


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


