//
//  main.c
//  cpp_csv2arff_v1
//
//  Created by MACPro on 9/21/2558 BE.
//  Copyright © 2558 Wana. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    /*
     concept
     1. open .csv file 'r'
     2. <read> first line >> header
     3. ask for attribute type each column is numeric or nominal
     count attributes number
     4. <close> .csv file
     
     [Relation / Attribute Section]
     5. open .arff file 'w' <create new file>
     6. <write>@relation whatever<\n>    //fix
     ..newlines..
     @attribute [A] [numeric or nominal]<\n>
     @attribute [B] numberic<\n>
     @attribute ...
     @attribute [E] nominal {m1,m2,m3,...}<\n>
     ..newlines..
     7. <close>
     
     [Data Section]
     @data
     ..newline..
     8. open .arff file 'a'
     9. open .csv file 'r'
     10. <read> .csv skip first line
     11. <write> .arff for each data
     data from .csv change , and ; to ' '
     12. <close> .arff and .csv file
     */
    
    FILE *csvfile;
    char *csvfileName1 = "file_csv_2.csv";
    char *outarfffileName = "out_arff.arff";
    //1.
    csvfile = fopen(csvfileName1, "r");
    if (csvfile == NULL) {
        printf("File Not Found!\n");
        exit(0);
    }
    //2.
    //open : count attribute
    char ch;// = fgetc(csvfile);
    int numAttrb = 0;
    while ((ch = fgetc(csvfile)) != '\n') {
        if (ch==',' || ch==';') {
            numAttrb++;
        }
    }
    //end +1
    numAttrb++;
    fclose(csvfile);
    
    //open : type attribute
    csvfile = fopen(csvfileName1, "r");
    char attrs[numAttrb][50];
    
    int pNum = 0;
    int pChar = 0;
    //ch = fgetc(csvfile);
    while ((ch=fgetc(csvfile)) != '\n') {
        if (ch!=',' && ch!=';') {
            attrs[pNum][pChar] = ch;
            pChar++;
        }else{
            attrs[pNum][pChar] = '\0';
            pNum++;
            pChar = 0;
        }
    }
    //end of array + \0
    attrs[pNum][pChar] = '\0';
    fclose(csvfile);
    
    printf("Attributes : ");
    for (int i=0; i<numAttrb; i++) {
        printf("%s ",attrs[i]);
    }
    //3. ASK Attribute type ...
    printf("\nType of each attributes(%d) -- Numeric[N] or Nominal[!N]?\n",numAttrb);
    char aInput[numAttrb];
    printf("__ is : ");
    for (int i=0; i<numAttrb; i++) {
        scanf("%c",&aInput[i]);
    }
    printf("\n");
    
    //5. print @relation and @attribute
    FILE *outfile = fopen(outarfffileName, "w");
    fputs("@relation whatever\n\n", outfile);
    
    for (int i=0; i<numAttrb; i++) {
        if (aInput[i]=='N'||aInput[i]=='n') {
            fprintf(outfile,"@attribute %s numeric\n",attrs[i]);
        }else{
            fprintf(outfile,"@attribute %s nominal\n",attrs[i]);
        }
    }
    fputs("\n@data\n", outfile);
    fclose(outfile);
    
    //8. print @data
    FILE *csvin = fopen(csvfileName1, "r");
    FILE *arffout = fopen(outarfffileName, "a");
    int lineIndex = 0;
    char ch1;
    while ((ch1 = fgetc(csvin)) != EOF) {
        if (lineIndex > 0) {
            if (ch1 == ',' || ch1==';') {
                fprintf(arffout, " %c ",ch1);
            }else{
                fputc(ch1, arffout);
            }
        }
        
        if (ch1=='\n') {
            lineIndex++;
        }
    }
    
    fclose(csvin);
    fclose(arffout);
    
    
    //FINISH
    printf("Convert file %s to %s has been finished.\n",csvfileName1,outarfffileName);
    printf("open...\n\n");
    
    arffout = fopen(outarfffileName, "r");
    char buf[100];
    while (fgets(buf, 100, arffout) != NULL) {
        printf("%s",buf);
    }
    
    printf("\n\nend...");
    return 0;
}

