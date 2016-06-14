# ESPfire

Gets latest emergency information for Aarhus Firestation, so I can see why the firetrucks are rolling out.


This should get you going: curl --silent http://www.112-aarhus.dk/viewpage.php?page_id=169 | head -n 116 | tail -n 3
pipe that into: "iconv -f iso8859-1 -t utf-8" to get æøå

But wait! 112-aarhus gets their data from: http://www.odin.dk/RSS/RSS.aspx?beredskabsID=1110
So you could use:
curl --silent http://www.odin.dk/RSS/RSS.aspx?beredskabsID=1110 | head -c 590 | tail -c 215