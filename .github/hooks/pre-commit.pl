#!/usr/bin/perl

use strict;
use warnings;

my $filename = `git rev-parse --show-toplevel`;
chomp($filename);
$filename = $filename . "/CMakeLists.txt";
my $data = read_file($filename);
my $regex = qr/project\((\s*)(\S+)(.*?)VERSION(\s*)(\d+)\.(\d+)\.(\d+)(.*?)\)/xsp;
$data = $data =~ s/$regex/project($1$2$3VERSION$4$5.$6.${\($7 + 1)}$8)/rg;
write_file($filename, $data);
system("git add \$(git rev-parse --show-toplevel)/CMakeLists.txt");
exit;

sub read_file {
  my ($filename) = @_;
  open my $in, '<:encoding(UTF-8)', $filename or die "Could not open '$filename' for reading $!";
  local $/ = undef;
  my $all = <$in>;
  close $in;
  return $all;
}

sub write_file {
  my ($filename, $content) = @_;
  open my $out, '>:encoding(UTF-8)', $filename or die "Could not open '$filename' for reading $!";;
  print $out $content;
  close $out;
  return;
}
