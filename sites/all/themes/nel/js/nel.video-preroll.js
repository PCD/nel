(function ($) {

  Drupal.behaviors.nelVideoPreroll = {
    attach: function (context, settings) {
      $('body', context).once('videoPreroll', function () {
        // License
        jwplayer.key="5jvmC+v3iu8mxjZIOcZ+4SWH4VyOfLEyg+eJ3tcGi7s=";
        
        // Get Vars
        preview_path = $('#preroll-player').attr('data-preview');
        preroll_path = $('#preroll-player').attr('data-preroll');
        video_path = $('#preroll-player').attr('data-video');
        plugin_path = $('#preroll-player').attr('data-plugin');
        
        // Initialize Video
        jwplayer('preroll-player').setup({ 
          playlist: [
            {
              autostart: 'true',
              image: preview_path,
              file: preroll_path,
              width: '100%', 
              aspectratio: '4:3', 
              stretching: 'fill'
            }, {
              autostart: 'true', 
              file: video_path,
              width: '630', 
              aspectratio: '4:3', 
              stretching: 'fill'
            }
          ], 
          plugins: {
            plugin_path: {}
          }
        });
      });
    }
  };

})(jQuery);