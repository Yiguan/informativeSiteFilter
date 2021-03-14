# informativeSiteFilter

Filter informative sites for a pedigree haplotype 

In a phased VCF file which has:

+ one trio:

```
father mother offspring
```
+ multiple offspring:

```
father mother offspring1 offspring2 offspring2
```

We can use `bcftools` to extract the phased haplotypes in the family:

```bash
bcftools convert --hapsample --vcf-ids 4.pedigree.phased.vcf.gz -o example
```

The output file from `bcftools` is, for example:

```
$head example.hap 
4 4:3321_G_T 3321 G T 0* 0* 1* 1* 0 1 0 1 0 1 0 1 0 1
4 4:5233_T_A 5233 T A 0* 0* 0 1 0 1 0 1 0* 0* 0* 0* 0 1
4 4:6342_T_A 6342 T A 0* 0* 1* 1* 0* 1* 0* 1* ? ? 0* 0* 0* 1*
4 4:7758_A_G 7758 A G 1* 1* 1* 1* 1* 1* 1* 1* 1* 1* 1* 1* 1* 1*
4 4:26044_T_A 26044 T A 0* 0* 1 0 0* 0* 0* 0* 0* 0* 0* 0* 0* 0*
4 4:26241_T_G 26241 T G 1* 1* ? ? 1* 1* 1* 1* 1* 1* 1* 1* 1* 1*
4 4:33876_A_G 33876 A G 0* 0* 1* 1* 0 1 0 1 0 1 0 1 0 1
4 4:34093_A_T 34093 A T 0* 0* 1 0 0* 0* 0* 0* 0 1 0 1 0* 0*
4 4:34258_G_C 34258 G C 0* 0* ? ? ? ? 0* 1* ? ? 0* 1* 0* 1*
4 4:34270_G_T 34270 G T ? ? ? ? ? ? 0* 1* ? ? 0* 1* ? ?
```
column 6-7: the haplotyps from father;

column 8-9: the haplotypes from mother;

column 10-11, 12-13,...: The haplotypes from offspring.

`*` indicates unphased genotypes, `?` indicates the missing genotypes.

The purpose of this repository is to filter informative sites from the above hap file.

`informtive sites`: one of the parents is heterozygous; its parterner and offspring cannot be both homozygous.

## Usage


### input file

`bcftools` converted hap files, as is described above.


### compile and run

```bash
gcc -std=c11 -o filterInfoSites main.c
./filterInfoSites example.hap example.out
```

./filterInfoSites input_file output_file

### output file

```
cat example.out 
4	4:5233_T_A	5233	T	A	0	0	0	1	0	1	0	1	0	0	0	0	0	1
4	4:26044_T_A	26044	T	A	0	0	1	0	0	0	0	0	0	0	0	0	0	0
4	4:34093_A_T	34093	A	T	0	0	1	0	0	0	0	0	0	1	0	1	0	0
```



