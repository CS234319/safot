% location="Jerusalem , Israel"
server="http://www.Google.com/ig/api"
request="$server?weather=$location"
wget -q -O - $request |\
tr " < >" "\012\012" |\
grep " condition data " |\
head -n 1 |\
sed -e 's/^.*="//' -e 's/"\/*//' |\
tr 'A -Z' 'a -z'
