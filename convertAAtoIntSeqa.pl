#function
# Author: Lalitha Viswanathan
# Affiliation: Tata Consultancy Services 
#####################################################
sub readfile
{
%hash_lib={};
@array_lib={};
$fname=$_[0];
print $fname." is the name to be processed\n";
open(fhandle,$fname);
$line=<fhandle>;
	while($line)
	{
		@temp_array=split('\t',$line);
		push(@array_lib,@temp_array);
		$line=<fhandle>;
	}
close(fhandle);
%hash_lib=@array_lib;
print "after processing heptamer library\n";
sort(%hash_lib);
}
#####################################################
sub process
{
$readfilename=$_[0];
$writefilename=$_[1];
print "the names are " .$readfilename."and ". $writefilename;
open(fr,$readfilename);
open(fw,">$writefilename");
$sentence='';
$entry=<fr>;
	while($entry)
	{
		if(substr($entry,0,1) ne '>')
		{
			chomp($entry);
			$sentence.=$entry;
		}	
		else
		{
			if($sentence)
			{
				for($i=0;$i<length($sentence)-6;$i++)
				{
				#	print $i." ";
					$hept=substr($sentence,$i,7);
					$heptbk=$hept;
					if(($heptbk !~ m/\*/)&&(substr($heptbk,0,1) ne 'S'))
					{
						if (exists($hash_lib{$hept}))
						{
							chomp($num=$hash_lib{$hept});
							if($num > 9)
							{
							$num=9;
							}	
						}
						else
						{
						$num=0;
						}
						print fw $num;	
					}
					elsif ($heptbk =~ m/\*/)
					{	
						print fw "*";
						$i=$i+6;
					}
					elsif (substr($heptbk,0,1) eq 'S')
					{
						print fw 'S'; 
					}
					$hept="";
				}
			$sentence="";
			}
			print fw "\n".$entry;
		}
	$entry=<fr>;
	}
close(fr);
close(fw);
}
readfile("hept1.lib.sort");
process("output1.txt","intrepresentation1.txt");
readfile("hept2.lib.sort");
process("output2.txt","intrepresentation2.txt");
readfile("hept3.lib.sort");
process("output3.txt","intrepresentation3.txt");
readfile("hept4.lib.sort");
process("output4.txt","intrepresentation4.txt");
readfile("hept5.lib.sort");
process("output5.txt","intrepresentation5.txt");
readfile("hept6.lib.sort");
process("output6.txt","intrepresentation6.txt");
#####################################################