(function ($) {

  Drupal.behaviors.uncacheThis = {
    attach: function (context, settings) {
      $('#uncache-this-button', context).once('highlightning', function () {
        $(this).click(uncacheThisClick);
      });
    }
  };
  
  /**
   * Click event for uncacheThis Button.
   */
  function uncacheThisClick(e) {
    if ( $(this).hasClass('uncached') ) {
      e.preventDefault();
      return false;
    }

    button = $(this);
    $(button).removeClass('uncached');
    url = $(button).attr('href');
    uncaching = Drupal.t('unCaching This...');
    $(button).addClass('uncaching').text(uncaching);
    $.post(url, function(data){
      uncached = Drupal.t('unCached');
      $(button).removeClass('uncaching').addClass('uncached').text(uncached);
      alert(Drupal.t('This Page has been uncached.'));
    }, 'json');
    e.preventDefault();
  }

})(jQuery);