#!/usr/bin/perl -w
# Should be run with -Mutf8 -CSD

use feature ":all";

# Try to understand your code.
while (<>) { # -n
  s/[\x00-\xff]//g;
  $_{$_}++ for split //;
  END {
    printf qq[%04x %s\n], $_, chr $_ for grep { $_ > 10000 } map ord, sort keys %_;
  }
}

