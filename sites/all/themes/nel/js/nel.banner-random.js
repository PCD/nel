(function ($) {
  Drupal.behaviors.nelBannerRandom = {
    attach: function (context, settings) {
      $('.field-collection-item-field-generic-block-banner, ' + 
        '.field-collection-item-field-generic-block-banner2, ' + 
        '.field-collection-item-field-generic-block-banner3', context).once('videoPreroll', function () {
        if ( $(this).hasClass('one-block-two-columns') ) {
          // Process One Random Block.
          blocks = $(this).find('.banner-block');
          randomizeBlocks(blocks);
        } else if ( $(this).hasClass('two-block-one-column') ) {
          // Process Two Random Blocks.
          left_blocks = $(this).find('> .block-banner-left .banner-block');
          //randomizeBlocks(left_blocks);
          right_blocks = $(this).find('> .block-banner-right .banner-block');
          //randomizeBlocks(right_blocks);
        }
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
