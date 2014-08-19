(function ($) {

  /**
   * The recommended way for producing HTML markup through JavaScript is to write
   * theming functions. These are similiar to the theming functions that you might
   * know from 'phptemplate' (the default PHP templating engine used by most
   * Drupal themes including Omega). JavaScript theme functions accept arguments
   * and can be overriden by sub-themes.
   *
   * In most cases, there is no good reason to NOT wrap your markup producing
   * JavaScript in a theme function.
   */
  Drupal.theme.prototype.nelExampleButton = function (path, title) {
    // Create an anchor element with jQuery.
    return $('<a href="' + path + '" title="' + title + '">' + title + '</a>');
  };

  /**
   * Behaviors are Drupal's way of applying JavaScript to a page. In short, the
   * advantage of Behaviors over a simple 'document.ready()' lies in how it
   * interacts with content loaded through Ajax. Opposed to the
   * 'document.ready()' event which is only fired once when the page is
   * initially loaded, behaviors get re-executed whenever something is added to
   * the page through Ajax.
   *
   * You can attach as many behaviors as you wish. In fact, instead of overloading
   * a single behavior with multiple, completely unrelated tasks you should create
   * a separate behavior for every separate task.
   *
   * In most cases, there is no good reason to NOT wrap your JavaScript code in a
   * behavior.
   *
   * @param context
   *   The context for which the behavior is being executed. This is either the
   *   full page or a piece of HTML that was just added through Ajax.
   * @param settings
   *   An array of settings (added through drupal_add_js()). Instead of accessing
   *   Drupal.settings directly you should use this because of potential
   *   modifications made by the Ajax callback that also produced 'context'.
   */
  Drupal.behaviors.nelExampleBehavior = {
    attach: function (context, settings) {
      $(document).ready(function(){
        $('audio,video').mediaelementplayer();
      });
    }
  };
  
  Drupal.behaviors.nelStickyHeader = {
    attach: function (context, settings) {
      paddingTop = 0;
      window_width = parseInt($(window).width(), 10);
      if ( window_width > 996 ) {
        paddingTop = parseInt($('body').css('padding-top'), 10);
      }
      $('.navigation-wrapper').waypoint('sticky', {
        offset: paddingTop
      });
    }
  };
  
  Drupal.behaviors.nelTopCarousel = {
    attach: function (context, settings) {
      $(window).resize(topCarouselResize);
      $(window).load(topCarouselResize);
    }
  };

function topCarouselResize() {
  selector = '#block-views-slider-block article, ';
  selector += '#block-views-slider-block .views-slideshow-cycle-main-frame, ';
  selector += '#block-views-slider-block .views-slideshow-cycle-main-frame-row';
  
  window_width = parseInt($(window).width(), 10);
  if ( window_width <= 748 ) {
    window_width -= 16;
    carousel_width = 321/630*window_width;
    carousel_width = Math.min(321, carousel_width);
    carousel_width = parseInt(Math.max(196, carousel_width), 10);
    $(selector).height(carousel_width);
    //$(selector).css("cssText", "height: " + carousel_width + "px !important");
  } else if ( window_width <= 996 ) {
    $(selector).width(473);
    $(selector).height(321);
  } else {
    $(selector).width(630);
    $(selector).height(321);
    //$(selector).css("cssText", "height: 321px !important");
  }
  $('#block-views-slider-block .views_slideshow_cycle_main').cycle('pause');
  $('#block-views-slider-block .views_slideshow_cycle_main').cycle('resume');
}

})(jQuery);
