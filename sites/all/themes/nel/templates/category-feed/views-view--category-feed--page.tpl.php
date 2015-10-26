<?php drupal_add_http_header('Content-Type', 'text/xml; charset=UTF-8');?>
<?php print '<?xml version="1.0" encoding="utf-8" ?>';?><rss version="2.0" xml:base="<?php print $base_url;?>/all" xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:content="http://purl.org/rss/1.0/modules/content/" xmlns:foaf="http://xmlns.com/foaf/0.1/" xmlns:og="http://ogp.me/ns#" xmlns:rdfs="http://www.w3.org/2000/01/rdf-schema#" xmlns:sioc="http://rdfs.org/sioc/ns#" xmlns:sioct="http://rdfs.org/sioc/types#" xmlns:skos="http://www.w3.org/2004/02/skos/core#" xmlns:xsd="http://www.w3.org/2001/XMLSchema#" xmlns:media="http://search.yahoo.com/mrss/">
  <channel>
    <title>nayaritenlinea.mx</title>
    <link>http://local.nel.com/all</link>
    <description>El Portal de Nayarit</description>
    <language>en</language>
    <?php print $rows; ?>
  </channel>
</rss>
<?php exit;?>