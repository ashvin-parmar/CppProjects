IUnitOfMeasuremenr *unitOfMearsurement;
int sizeOfTitle;

//validations
if(unitOfMeasurement==NULL) throw string("NULL value provided");
sizeOfTitle=unitOfMeasurement->getTitle().size();
if(sizeOfTitle==0) throw string("Empty title is provided, please give a title.");
if(sizeOfTitle>25) throw string("Title can not more than 25 characters, please short your title")
if(unitOfMeasurement->getCode()==0) throw string("set Code should be 0");

//opening data file for searching data (duplicacy removal)
f=fopen(datafile,r);

fread(&header,f)