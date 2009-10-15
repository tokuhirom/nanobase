use inc::Module::Install;

my $e = env_for_c(CPPPATH => 'extlib');
$e->enable_warnings();
$e->test("t/01_encode", "t/01_encode.c");

tests 't/*.t';

WriteMakefileForC;
