(function ($) {
  Drupal.behaviors.nelVideoChannel = {
    attach: function (context, settings) {
      $(window).load(function(){
        thisheight = 0;
        $('.view-lo-mas-visto .views-row').each(function(){
          itemheight = parseInt($(this).outerHeight(true), 10);
          thisheight = Math.max(thisheight, itemheight);
        });
        
        $('.view-lo-mas-visto .views-row').height(thisheight);
      });
    }
  };
  
})(jQuery);
