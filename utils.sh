#!/bin/bash
# If you have missed days, you can catch up using:
# for X in {1..10}; do ./utils.sh $X; done
args=("$@")
if (( $# < 1 )); then
    echo "Please enter a daynumber in!"
    exit 1
fi
# Add zero to numbers < 10
day=${args[0]}


session=`cat session`
dirname="day$day"
# Create basic files
rm -r $dirname 2> /dev/null; mkdir $dirname
cp sample.cpp "$dirname/${day}_1.cpp"
cp sample.cpp "$dirname/${day}_2.cpp"
touch "$dirname/input.sample" "$dirname/input.in"

# Fetch input data.
inputIN=`curl -s https://adventofcode.com/2022/day/$day/input --cookie "session=$session"`
# Put it into file.
cat <<< "$inputIN" > "$dirname/input.in"

# Read whole day page
page=`curl -s https://adventofcode.com/2022/day/$day --cookie "session=$session"`

# Delete everything before first example.
t=`echo "$page"  | sed -e '1,/For example/d'`

# Perl code to apply the regex
out=`perl -e'my $data = do { local $/; <> };
     my $regex = qr/(?<=<code>)(.|\n)*?(?=<\/code>)/mp;
     if ( $data =~ /$regex/ ) {print "${^MATCH}"}' <<< $t`

# Finally store the result in the sample file.
cat <<< "$out" > $dirname/input.sample
exit 0