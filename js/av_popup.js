/**
 * Contains javascript to display popups.
 *
 * @file av_popup.js
 */

(function ($) {
  var basePath;

  Drupal.behaviors.avPopup = {
    attach: function (context, settings) {
      var avPopup = Drupal.settings.avPopup;

      // Remove cookie conform settings.
      if(avPopup.reset) {
        $.cookie("av_popup", null, { path: '/' });
      }

      var $cookie = $.cookie("av_popup");
      if (!$cookie) {
        setTimeout(function () {
          $.magnificPopup.open({
            key: 'av-popup',
            showCloseBtn: false,
            enableEscapeKey: false,
            closeOnBgClick: false,
            closeOnContentClick: false,
            items: {},
            type: 'inline',
            inline: {
              markup: avPopup.markup
            },
            callbacks: {
              open: function () {
                $.magnificPopup.instance.close = function () {
                  // Lets set o cookie with expired  period.
                  $.cookie("av_popup", true, {path: '/', expires: 48 * 3600 * 1000});
                  $.magnificPopup.proto.close.call(this);
                };
              }
            }
          });
        }, avPopup.delays.up * 1000);

        // Close popup after specific delay.
        setTimeout(function () {
          $.magnificPopup.close();
        }, avPopup.delays.up * 1000 + avPopup.delays.close * 1000);

      }
    }
  };

})(jQuery);
