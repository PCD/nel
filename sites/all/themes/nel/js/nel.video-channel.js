(function ($) {
  Drupal.behaviors.nelVideoChannel = {
    attach: function (context, settings) {
      $(window).load(function(){
        $('.view-lo-mas-visto').each(function(){
          thisheight = 0;
          $(this).find('.views-row').each(function(){
            itemheight = parseInt($(this).height(true), 10);
            thisheight = Math.max(thisheight, itemheight);
          });
          
          $(this).find('.views-row').height(thisheight);
        });
      });
    }
  };
  
})(jQuery);
