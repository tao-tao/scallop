#include "gtf_exon.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstdio>

gtf_exon::gtf_exon(const string &s)
{
	parse(s);
}

int gtf_exon::parse(const string &s)
{
	char buf[10240];
	stringstream sstr(s);
	sstr>>buf;
	seqname.assign(buf);
	sstr>>buf;
	source.assign(buf);
	sstr>>buf;
	feature.assign(buf);
	sstr>>start>>end;
	sstr>>buf;
	if(buf[0] == '.') score = -1;
	else score = atof(buf);
	sstr>>buf;
	strand = buf[0];
	sstr>>buf;
	frame = buf[0];

	char buf2[10240];

	while(sstr.eof() == false)
	{
		sstr>>buf>>buf2;
		if(string(buf) == "transcript_id")
		{
			string ss(buf2);
			transcript_id = ss.substr(1, ss.size() - 3);
		}
		else if(string(buf) == "gene_id")
		{
			string ss(buf2);
			gene_id = ss.substr(1, ss.size() - 2);
		}
		else if(string(buf) == "expression")
		{
			string ss(buf2);
			expression = (int32_t)(atoi(ss.substr(1, ss.size() - 2).c_str()));
		}
	}
}

int gtf_exon::print()
{
	printf("%s\t%s\t%s\t%d\t%d\t%.1lf\t%c\t%c\ttranscript_id \"%s\"; gene_id \"%s\"; expression \"%d\"\n",
			seqname.c_str(), source.c_str(), feature.c_str(), start, end, score, strand, frame,
			transcript_id.c_str(), gene_id.c_str(), expression);
	return 0;
}

bool gtf_exon::operator<(const gtf_exon &ge) const
{
	if(start < ge.start) return true;
	else return false;
}
