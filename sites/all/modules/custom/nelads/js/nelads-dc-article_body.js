googletag.cmd.push(function() {
  googletag.defineSlot('/15651346/Article-Body-300x250', [300, 250], 'div-gpt-ad-1446621104256-0').addService(googletag.pubads());
  // Start Custom Criteria
  google_class = document.getElementsByTagName('body')[0].getAttribute('data-google-class');
  googletag.pubads().setTargeting("google_class", google_class);
  // Candidato class.
  candidato_class = document.getElementsByTagName('body')[0].getAttribute('data-candidato-class');
  googletag.pubads().setTargeting("candidato_class", candidato_class);
  // End Custom Criteria
  googletag.pubads().enableSingleRequest();
  googletag.enableServices();
});