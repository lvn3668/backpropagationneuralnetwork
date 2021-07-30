# Author: Lalitha Viswanathan
# Affiliation: Tata Consultancy Services 
#####################################################
sub process_file
{
	open(fread,$_[0]);
	print "inside file\n";
	$line=<fread>;
	while($line)
	{
		print $line;
		if(substr($line,0,1) ne '>')
		{
		$totalength=length($line);
		print $totalength."\n";
		$line1=$line;
		while($ret= $line1=~ s/\d/x/)
		{
			$totalscore+=$ret;
		}
		$line1=$line;
		while($ret =$line1=~ s/0/z/)
		{
			$zeroes+=$ret;
		}
		$mean=$totalscore/$totalength;
		$frac_of_zeroes=$zeroes/$totalength;
		#computing variance
		for($i=0;$i<$totalength;$i++)
		{
			if((substr($line,$i,1) ne 'S')&&(substr($line,$i,1) ne '*'))
			{
				$varsum+=(substr($line,$i,1)-$mean);
			}
		}
		$varsum_mom_skew=$varsum;
		$varsum*=$varsum;
		$variance=$varsum/$totalength;

		#computing moment of skewness
		$varsum_mom_skew*=$varsum;
		$mom_skewness=($varsum_mom_skew/$totalength)/sqrt($variance*$variance*$variance);
		#max_continuous_stretch
		$max_continuous_stretch=0;
		$length_cs=0;
		for($i=0;$i<$totalength;$i++)
		{
			$continuous_stretch=$i;	
			while( (substr($line,$continuous_stretch,1) ne 'S')&& (substr($line,$continuous_stretch,1)ne'*')&& (substr($line,$continuous_stretch,1) ne 0))
			{
			$continuous_stretch++;	
			$length_cs++;
			}
			if($length_cs>$max_continuous_stretch)
			{
				$max_continuous_stretch=$length_cs;
			}
		}
		}
	$line=<fread>;	
	}
close(fread);
print $mean."	".$frac_of_zeroes."	".$mom_skewness."	".$variance."	".$max_continuous_stretch;
}
process_file("wrong.txt");
#####################################################
