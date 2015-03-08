(function ($) {

  Drupal.behaviors.nelMicroHighlightning = {
    attach: function (context, settings) {
      $('.field-collection-item-field-generic-block, ' +
        '.field-collection-item-field-sidebar-block, ' + 
        '.field-collection-item-field-sidebar-block-2', context).once('highlightning', function () {
        block = $(this).parent();
        if ( $(block).find('> .field-collection-view-links > li.edit a').length > 0 ) {
          processThisBlock(block);
        }
      });
    }
  };

/**
 *
 */
function processThisBlock(block) {
  $(block).addClass('generic-block-wrapper').append('<div class="generic-block-highlightning"></div>');
  $(block).find('> .field-collection-view-links > li.edit a').mouseover(mouseOver).mouseout(mouseOut);
  $(block).find('> .field-collection-view-links > li.delete a').mouseover(mouseOver).mouseout(mouseOut);
}

/**
 *
 */
function mouseOver() {
  if ( $(this).parent().hasClass('delete') ) {
    $(this).parent().parent().parent().addClass('red');
  } else {
    $(this).parent().parent().parent().addClass('on');
  }
}

/**
 *
 */
function mouseOut() {
  if ( $(this).parent().hasClass('delete') ) {
    $(this).parent().parent().parent().removeClass('red');
  } else {
    $(this).parent().parent().parent().removeClass('on');
  }
}

})(jQuery);