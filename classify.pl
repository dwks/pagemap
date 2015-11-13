#!/usr/bin/perl

while(<>) {
    chomp;
    if(/pfn (\S+)/) {
        push @{ $pfn{$1} }, $_;
    }
}

for my $i (sort keys %pfn) {
    next if(@{ $pfn{$i} } <= 1);  # skip non-shared pages

    for my $line (@{ $pfn{$i} }) {
        printf "%-8s => %s\n", $i, $line;
    }
}
