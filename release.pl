#!/usr/local/bin/perl

$custom = "";
$custom_ = "";
$customer_name = "";
$sub_customer_name = "";
$project = "GPRS";
$ini = "make.ini";
$bld_name = "";
$mak_name = "";
$chip_ver = "";
$VERNO = "";
$release_dir = "build";
$db_file = "";
$bin_folder = "";
$elf_file = "";
$sym_file = "";
$dbginfo_file = "";
$mail_body = ".\\$release_dir\\mail_body.txt";
$version_dir = "";
$mail_flag = 0;
#ӳ�䵽���ص��̷����ɸ���ʵ������޸�
#$server_path = "M:\\��Ű����";
$server_path = "Z:\\��������汾\\A62";
if ($#ARGV == 1) {
    if ($ARGV[0] =~ /-mail/i) {
    	$mail_flag = 1;
    	$custom = $ARGV[1];
    } else {	
       $custom = $ARGV[0];
    }
} elsif ($#ARGV == 0) {
    if ($ARGV[0] =~ /-mail/i) {
    	$mail_flag = 1;
    } else {	
       $custom = $ARGV[0];
    }
}
if ($mail_flag == 1){
    my $flat_set = "d:\\flatsetting\\flat.ini";
    if (!-e $flat_set) {
    	CheckMailSet();
    	exit 1;
    }
}
if (($custom eq "")&&(-e $ini)) {
   	   open (FILE_HANDLE, "<$ini") or die "cannot open $ini\n>>>��������û�������������Ŀ<<<\n";
   	   while (<FILE_HANDLE>) {
            if (/^(\S+)\s*=\s*(\S+)/) {
              $keyname = $1;
              $${keyname} = $2;
              chomp($${keyname});
            }
        }
        close FILE_HANDLE;
}
$bld_name = "make\\Verno_${custom}.bld";
$mak_name = "make\\${custom}_${project}.mak";
if (-e "$mak_name") {
   my $flash_size = GetFeature($mak_name, "SIP_SERIAL_FLASH_SIZE");
   my $plat = GetFeature($mak_name, "PLATFORM");
   $customer_name = GetFeature($mak_name, "CUSTOMER_NAME");
   $sub_customer_name = GetFeature($mak_name, "SUB_CUSTOMER_NAME");
   if ($plat eq "MT6260") {
       if ($flash_size eq "NONE") {
          $chip_ver = "MT6260";
       } elsif ($flash_size eq "32M_BITS") {
          $chip_ver = "MT6260D";
       } elsif ($flash_size eq "24M_BITS") {
          $chip_ver = "MT6260M";
       } 
   }
} else{
	print(">>>����û�д����ͱ������Ŀ<<<\n");
	exit 1;
}

if (-e "$bld_name") {
   open (FILE_HANDLE, "<$bld_name") or die "cannot open $bld_name\n";
   while (<FILE_HANDLE>) {
        if (/^(\S+)\s*=\s*(\S+)/) {
          $keyname = $1;
          $${keyname} = $2;
          chomp($${keyname});
          last;
        }
    }
    close FILE_HANDLE;
} else{
	print(">>>����û�д����ͱ������Ŀ<<<\n");
	exit 1;
}

if (!-d $release_dir) {
   mkdir("$release_dir");
}
my $build_date = getTime();
my $build_date = $build_date->{date};
$version_dir = "${VERNO}_${build_date}";
#$version_dir = "${VERNO}";
if (-e "$release_dir\\$version_dir") {
    use File::Path;
    -d $_?rmtree($_):unlink $_ foreach (<$release_dir/$version_dir/*>);
} else {
	print "create dir $version_dir\n";
	mkdir("$release_dir\\$version_dir");
}

my $db_dir = "./tst/database_classb";
my $file;
my @dir;
my $verno_ = $VERNO;
$verno_ =~ s/\./_/g;
opendir(DIR, $db_dir) or die "can't open the directory ${db_dir}!";
@dir = readdir DIR;
closedir(DIR);
foreach $file (@dir) {
  if ($file =~ /^BPLGUInfoCustomAppSrcP.*$verno_$/i) {
    $db_file = $file;
    last;
  }
}
if ($db_file eq ""){
   print "\ndatabase�ļ�${db_dir}/${db_file}�����ڣ������Ƿ�ɹ��������Ŀ!\n\n";
   exit 1;
}
use File::Copy;
my $dest_file = "$release_dir/$version_dir";
print "copy database: ${db_dir}/${db_file}\n";
copy("${db_dir}/${db_file}",$dest_file) or die "�޷�����database�ļ� ${db_dir}/${db_file}�������Ƿ�ɹ��������Ŀ!\n";

my $build_dir = "build/${custom}";
my $file;
my @dir;
my $custom_ex = "${custom}_PCB01";
opendir(DIR, $build_dir) or die "�޷���Ŀ¼ ${build_dir}�������Ƿ�ɹ��������Ŀ!\n";
@dir = readdir DIR;
closedir(DIR);
foreach $file (@dir) {
  #if ($file =~ /^$custom_ex.*$verno_\.bin$/i) {
  if ($file =~ /^$custom_ex.*\.bin$/i) {
    $bin_folder = $file;
  }
  if ($file =~ /^$custom_ex.*\.elf$/i) {
    $elf_file = $file;
  }
  if ($file =~ /^$custom_ex.*\.sym$/i) {
    $sym_file = $file;
  }
  if ($file =~ /^DbgInfo_.*${verno_}.*/i)
  {
    $dbginfo_file = $file;
  }
  if (($bin_folder ne "") && ($elf_file ne "") && ($sym_file ne "") && ($dbginfo_file ne "")){
     last;
  }
}
if ($bin_folder eq ""){
   print "\n�޷���BIN������Ŀ¼�������Ƿ�ɹ��������Ŀ!\n\n";
   exit 1;
}
use File::Copy;
print "copy sym: ${build_dir}/${sym_file}\n";
copy("${build_dir}/${sym_file}",$dest_file) or die "�޷�����sym�ļ� ${build_dir}/${sym_file}�������Ƿ�ɹ��������Ŀ!\n";
print "copy elf: ${build_dir}/${elf_file}\n";
copy("${build_dir}/${elf_file}",$dest_file) or die "�޷�����elf�ļ� ${build_dir}/${elf_file}�������Ƿ�ɹ��������Ŀ!\n";
print "copy DbgInfo: ${build_dir}/${dbginfo_file}\n";
copy("${build_dir}/${dbginfo_file}",$dest_file) or die "�޷�����DbgInfo�ļ� ${build_dir}/${dbginfo_file}�������Ƿ�ɹ��������Ŀ!\n";

my $file;
my @dir;
my $bin_dir = "${build_dir}/${bin_folder}";
my $zip_path = "./plutommi/Customer/ResGenerator/7za";
if (-e "${dest_file}\\${VERNO}") {
	system("rmdir /S /Q ${dest_file}\\${VERNO}");
}
mkdir("${dest_file}\\${VERNO}");
opendir(DIR, $bin_dir) or die "�޷���Ŀ¼ ${bin_dir}�������Ƿ�ɹ��������Ŀ!\n";
@dir = readdir DIR;
closedir(DIR);
use File::Copy;
foreach $file (@dir) {
  if (($file eq "ROM") ||($file eq "VIVA")||($file eq "EXT_BOOTLOADER")) {
    copy("${bin_dir}/${file}","${dest_file}\\${VERNO}") or die "could not copy files :${bin_dir}/${file}!";
  } elsif ($file =~ /^scat$custom.*\.txt$/i) {
    copy("${bin_dir}/${file}","${dest_file}\\${VERNO}") or die "could not copy files :${bin_dir}/${file}!";
  } elsif ($file =~ /.*\.cfg$/) {
    copy("${bin_dir}/${file}","${dest_file}\\${VERNO}") or die "could not copy files :${bin_dir}/${file}!";
  } elsif ($file =~ /^$custom.*$verno_\.bin$/i) {
    copy("${bin_dir}/${file}","${dest_file}\\${VERNO}") or die "could not copy files :${bin_dir}/${file}!";
  }
}

chdir("${dest_file}");
system("../../${zip_path} a -tzip ${VERNO}\.zip ${VERNO}\\*");
system("../../${zip_path} a -tzip ${VERNO}\.zip ${db_file}");

if (-e $VERNO) {
	system("rmdir /S /Q ${VERNO}");
}
if (-e $db_file) {
	system("del /F /Q $db_file");
}
chdir("../");
if ($customer_name ne "")
{
  $custom_ = $customer_name;
} else {
  $custom_ = $custom;
}
if ($chip_ver ne "") {
   $custom_ = "${custom_}_${chip_ver}";
}
if (!-d "${server_path}\\${custom_}") {
   mkdir("${server_path}\\$custom_") or die "����Ŀ¼ ${server_path}\\$custom_ ʧ��!";
}
if ($sub_customer_name ne "")
{
  $custom_ = $custom_."\\${sub_customer_name}";
  if (!-d "${server_path}\\${custom_}") {
   mkdir("${server_path}\\$custom_") or die "����Ŀ¼ ${server_path}\\$custom_ ʧ��!";
  }
}
if (!-d "${server_path}\\${custom_}\\${version_dir}") {
   mkdir("${server_path}\\$custom_\\${version_dir}") or die "����Ŀ¼ ${server_path}\\$custom_\\${version_dir} ʧ��!";
}
my $result = system("xcopy /S /Y ${version_dir} ${server_path}\\${custom_}\\${version_dir}");
if ($result !=0) {
  print "\n���������������ʱʧ��!\n��ȷ���Ƿ���Է���\"\\\\192.168.1.102\\��Ŀ�������Ŀ¼\",\n�����ѽ��ù���Ŀ¼ӳ��Ϊ����M��\n\n";
} else  {
  print "\n��ϲ���ѳɹ���������������������^_^\n\n";
  if ($mail_flag == 1) {
    #print "�Ƿ����ʼ�֪ͨ���Ժ���Ŀ�ȹ���Ա��(Y\/N):";
    #my $input= <STDIN> ;
    #chomp($input);
    #if (uc($input) eq "Y") {
      chdir("../");
      SetMailBody();
      SendMail();
    #} else {
    #	print "\n:):���������ǵ�֪ͨ���Ժ���ĿŶ��\n\n";
    #}
  } else {
      print "\n:):���������ǵ�֪ͨ���Ժ���ĿŶ��\n\n";
  }
}
sub getTime
{
    my $time = shift || time();
    my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime($time);
    
    $year += 1900;
    $mon ++;
    
    $min  = '0'.$min  if length($min)  < 2;
    $sec  = '0'.$sec  if length($sec)  < 2;
    $mon  = '0'.$mon  if length($mon)  < 2;
    $mday = '0'.$mday if length($mday) < 2;
    $hour = '0'.$hour if length($hour) < 2;
    
    my $weekday = ('Sun','Mon','Tue','Wed','Thu','Fri','Sat')[$wday];
    
    return { 'second' => $sec,
             'minute' => $min,
             'hour'   => $hour,
             'day'    => $mday,
             'month'  => $mon,
             'year'   => $year,
             'weekNo' => $wday,
             'wday'   => $weekday,
             'yday'   => $yday,
             'date'   => "$year-$mon-$mday"
          };
}

sub SendMail{
    my $sendto = ".\\sendto.txt";
    my $copyto = ".\\copyto.txt";
    my $flat_set = "d:\\flatsetting\\flat.ini";
    my $sendto_flag = "";
    my $copyto_flag = "";
    my $debug = "-debug -log blat.log -timestamp";
    
    if (-e $sendto) {
    	$sendto_flag = "-tf ${sendto}";
    } else {
    	my $sendto_list = GetFeature($flat_set, "SENDTO");
    	$sendto_flag = "-to ".$sendto_list;
    }
    if (-e $copyto) {
    	$copyto_flag = "-cf ${copyto}";
    } else {
    	my $copyto_list = GetFeature($flat_set, "COPYTO");
    	$copyto_flag = "-cc ".$copyto_list;
    }
    my $from= GetFeature($flat_set, "FROM");
    my $username=GetFeature($flat_set, "USER");
    my $password = GetFeature($flat_set, "PASSWD");
    my $subj = $VERNO;
    my $server = GetFeature($flat_set, "SERVER");
    print "\n�ʼ�������...\n";
    system("blat ${mail_body} $sendto_flag ${copyto_flag} -base64 -charset Gb2312 -subject ${subj} -server ${server} -f ${from} -u ${username} -pw ${password} ${debug}");
    print "\n�ʼ�������ɣ�\n";
}

sub SetMailBody{
   open(FILE, ">${mail_body}");
   print FILE "Dear All��\n\n";
   print FILE "    ${custom}��Ŀ����汾${VERNO}�ѷ������ص�ַ���£�\n\n";
   print FILE "\\\\192.168.1.102\\��Ŀ�������Ŀ¼\\${custom_}\\${version_dir}\n\n";
   print FILE "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
   close FILE;
}

sub CheckMailSet {
    my $flat_set = "d:\\flatsetting\\flat.ini";
    if (!-e $flat_set) {
       if (!-d "d:\\flatsetting") {
          mkdir("d:\\flatsetting") or die "����Ŀ¼ d:\\flatsetting ʧ��!\n";
       }
       open(FILE, ">$flat_set");
       print FILE "#�����ַ\nFROM = wancheng\@far-sightedmobile.com\n#�����˻�\nUSER = wancheng\@far-sightedmobile.com\n#��������\nPASSWD = XXXX123456\n";
       print FILE "#���ͷ�����(���ø�)\nSERVER = smtp.far-sightedmobile.com\n#�ռ���(����ռ����ö��Ÿ���)\nSENDTO = \"renyuxuan\@far-sightedmobile.com,chenxia\@far-sightedmobile.com\"\n";
       print FILE "#����(����ö��Ÿ���)\nCOPYTO = \"zhouzhipeng\@far-sightedmobile.com,xiaoyue\@far-sightedmobile.com\"\n";
       close FILE;
       print "��һ��ʹ���ʼ��������ȴ�\"${flat_set}\"��������\n\n";
       print "�Ƿ����ڱ༭��(Y\/N):";
       my $input= <STDIN> ;
       chomp($input);
       if (uc($input) eq "Y") {
         system("notepad.exe ${flat_set}");
         print "\nȷ���ʼ�������ȷ���������нű�\n";
       } else {   
          print "\n���ȴ�\"${flat_set}\"�������ã�Ȼ���������нű���\n";
       }
    }
}
sub GetFeature {
	  open (FILE_HANDLE, "<$_[0]") or die "can't open $_[0]\n";
  	  while (<FILE_HANDLE>) {
         if (/^(\S+)\s*=\s*(\S+)/) {
           if ($1 eq $_[1]) {
             close FILE_HANDLE;
             return $2;
           }
          }
       }
       close FILE_HANDLE;
       return "";
}
