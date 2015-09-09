(function ($) {
  Drupal.behaviors.nelMasonryGaleria = {
    attach: function (context, settings) {
      $('.node--article--full .galeria', context).once('masonry', function () {
        var $container = $(this);
        $container.imagesLoaded(function(){
          $container.masonry({
            itemSelector: '.masonryImage'
          });
        });
      });
    }
  };


})(jQuery);