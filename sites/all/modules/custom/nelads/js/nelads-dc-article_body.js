(function ($) {
  Drupal.behaviors.nelAdsDCArticleBody = {
    attach: function (context, settings) {
      $('body', context).once('nelAdsDCArticleBody', function () {
        googletag.cmd.push(function() {
          googletag.defineSlot('/15651346/Article-Body-300x250', [300, 250], 'div-gpt-ad-1446602697702-0').addService(googletag.pubads());
          // Start Custom Criteria
          googletag.pubads().setTargeting("google_class",settings.neladsdc.google_class);
          // End Custom Criteria
          googletag.pubads().enableSingleRequest();
          googletag.enableServices();
        });
      });
    }
  };
})(jQuery);
