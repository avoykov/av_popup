<?php
/**
 * @file
 * Represents template for rendering popup.
 *
 * Variables:
 *  $image - Background image.
 */
?>
<?php if ($close_btn): ?>
  <div id="av-popup-close-btn" class="mfp-close"></div>
<?php endif; ?>
<a id="av-popup-wrapper"
   style="background-image: url(<?php echo $image; ?>);  background-repeat: no-repeat; background-position: center;"
   href="<?php echo $url; ?>"
   target="<?php echo $target; ?>"></a>
