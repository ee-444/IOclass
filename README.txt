Implementation of an IOclass for Arduino hardware

RELEASE NOTES:
	02-09-11 - Project changes from using Atmel header files and just defined
		base address loactions for register changes.  Will later be included
		in a peripheral library archive of all object files from this organization.
		-sg

	02-16-11 - changes made to make better use of a single upload.bat file by giving it 
		arguments and placing it at the root folder for all AVR stuido projects.  Now
		we just need to find out how the program makes use of shortcuts for file handling
		within a project.  Then we wont have to rename the argument when different projects
		are open and worked on.  Newest upload.bat file is part of the ProjectName repo.
		-sg
