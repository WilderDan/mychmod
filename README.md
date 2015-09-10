$Id: README,v 1.1 2015/03/15 00:59:03 sentient Exp sentient $
Author:  Dan Wilder


======================
REVISION HISTORY
======================
    $Log: README,v $
    Revision 1.1  2015/03/15 00:59:03  sentient
    Initial revision



======================
Overview
======================

SYNOPSIS
    <EXECUTABLE> OPTION... PERMISSION... FILE...
 
DESCRIPTION
    Uses unix system calls and functions to change
    the permissions on one or more files.

OPTIONS
    	-u
	    Add permissions for user.
	-g
	    Add permissions for group.
	-o
	    Add permissions for other.
	-U
	    Remove permissions for user.
	-G
	    Remove permissions for group.
	-O
	    Remove permissions for group.

PERMISSIONS
    	r
	    READ
	w
	    WRITE
	x
	    EXECUTE

======================
INSTRUCTIONS
======================

  [BUILD PROJECT] 

      0) ***OPTIONAL*** 
         Specify EXECUTABLE name in Makefile. You can also include pathname to
         install in different directory. Default name is 'mychmod' in project's 
         root directory. 

      1) Run command 'make' from project's root directory.

  [EXECUTION]
      
      Run program from shell. Specify executable name followed by combination of
      options. After each option specify some combination of permissions (rwx). 
      Finally, specify 1 or more files to add/remove permissions for.
               
  [CLEANUP] 
 
      1) Run command 'make clean' from project's root directory.
           ~ executable and object files will be removed  
