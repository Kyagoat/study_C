int main(int argc, char* argv[])
{
   char* inputFilename;
   char* ouputFilename;
   if (argc < 3){
      fprintf(stderr, "You should provide an input and an output filenames. Aborting");
      exit(-1);
   }

   inputFilename = argv[1];
   outputFilename = argv[2];
}
