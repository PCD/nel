<div id=”facebookCount”></div>
<script>
var url = "http://nayaritenlinea.mx";
$.getJSON("http://graph.facebook.com/" + url, function (json)
{
$('#facebookCount').html(json.shares);
});
</script>