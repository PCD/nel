(function ($) {
  Drupal.behaviors.nelSidebarBannerRandom = {
    attach: function (context, settings) {
      $('.field-collection-item-field-sidebar-block .field-name-field-banner-block, ' + 
        '.field-collection-item-field-sidebar-block-2 .field-name-field-banner-block', context).once('banner-random', function () {
        // Process One Random Block.
        blocks = $(this).find('.banner-block');
        randomizeBlocks(blocks);
      });
    }
  };

/**
 * Get rid of all Banner blocks but one.
 */
function randomizeBlocks(blocks) {
  length = parseInt(blocks.length);
  if ( length < 2 ) {
    return;
  }
  
  chosen = getRandomInt(1, length) - 1;
  $(blocks).each(function(index){
    if ( index != chosen ) {
      $(this).remove();
    }
  });
}

/**
 * Returns a random integer between min (inclusive) and max (inclusive)
 * Using Math.round() will give you a non-uniform distribution!
 */
function getRandomInt(min, max) {
  return Math.floor(Math.random() * (max - min + 1)) + min;
}

})(jQuery);
