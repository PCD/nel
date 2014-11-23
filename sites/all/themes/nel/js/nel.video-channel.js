(function ($) {
  Drupal.behaviors.nelVideoChannel = {
    attach: function (context, settings) {
      $('.view-lo-mas-visto', context).once('sameHeight',function(){
        thisheight = 0;
        $(this).find('.views-row').each(function(){
          itemheight = parseInt($(this).outerHeight(true), 10);
          thisheight = Math.max(thisheight, itemheight);
        });
        
        $(this).find('.views-row').height(thisheight);
      });
    }
  };
  
})(jQuery);
