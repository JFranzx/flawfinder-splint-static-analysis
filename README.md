# flawfinder-splint-static-analysis
Download and install Flawfinder (http://www.dwheeler.com/flawfinder)  
and SPLINT (http://www.splint.org).

The tools have been used to statically analyze the code fragment in the file fragment.c
A report has been made consisting of two parts, one for each tool, containing:  

• Lines stating the major strengths and weaknesses of the tool.  
• A description of the output of the tool for the fragment.  
• A corrected version of the fragment where the vulnerabilities found with the tool have been removed.

In the "output" folder there are 3 folders:
- the "flawfinder_ analysis" folder: here is the fragment in its initial version and the one modified following the information obtained using the static analysis tool called Flawfinder.
- The "splint_analysis" folder: here too there is the fragment in its initial version and the one modified following the information obtained using the static analysis tool called Splint.
- the "merged_output" folder: here is the result of the merger of the two fragments at the end of the anilysis phase with the Flawfinder and Splint tools.
In the "report" folder there are all the files generated by Texlive including the final report in pdf format that has been written.
