#pragma once
#include <PSGL/psgl.h>

/// <summary>
/// Create, Dispose and Update the PSGL's environment
/// created to draw stuff into the PS3! :)
/// </summary>
class PSGLContext {
public:
    /// <summary>
    /// Initialize and setup PSGL's context.
    /// </summary>
    /// <param name="resolutions"><para>A 'priority-ordered' array of
    /// 'CellVideoOutResolutionId' values to try to use to set up
    /// PSGL.</para>
    /// For more information about these parameters, check 'GetBestVideoMode's
    /// documentation.</param>
    /// <param name="numResolutions">The number of resolutions given.</param>
    /// <returns>
    /// False if something failed while creating
    /// PSGL's context.
    /// </returns>
    bool Initialize(const unsigned int* resolutions, unsigned int numResolutions);
    /// <summary>
    /// Destroy/Close the context and other objects
    /// previously created for PSGL.
    /// </summary>
    void Dispose() const;

    void PreRender();
    void PostRender();

    /// <summary>
    /// Returns true if the PlayStation3 has
    /// a valid video output and is ready
    /// to display into the user's screen.
    /// </summary>
    static bool IsVideoOutputReady();
    /// <summary>
    /// Assign 'width' and 'height' proper values based on an
    /// ID from the 'CellVideoOutResolutionId' enum given.
    /// </summary>
    /// <example>
    /// <para>If "CELL_VIDEO_OUT_RESOLUTION_1080" is given, 'width'
    /// and 'height' will respectively be '1920' and '1080'.</para>
    /// <para>If "CELL_VIDEO_OUT_RESOLUTION_960x1080" is given, 'width'
    /// and 'height' will respectively be '980' and '1080'.</para>
    /// </example>
    /// <returns>
    /// 1 if the 'resolutionID' given is valid, 0 if not.
    /// </returns>
    static int GetResolutionFromResolutionID(unsigned int resolutionID, unsigned int& width, unsigned int& height);
    /// <summary>
    /// Take up a 'priority-ordered' array of 'CellVideoOutResolutionId'
    /// values and return the ID of the first value available from the array given.
    /// </summary>
    /// <remarks>
    /// Couldn't test it up myself, but based on Sony's documentation,
    /// you can use 'CELL_VIDEO_OUT_RESOLUTION_0000x0000' to render at
    /// a lower resolution that'll will automatically upscale the final
    /// buffer to 1080p instead of using 'CELL_VIDEO_OUT_RESOLUTION_000'.
    /// </remarks>
    /// <example>
    /// My most wanted resolution is '1920x1080', but if it isn't available,
    /// I's like to use '1280x720', I should input:
    /// <code>
    ///     resolutions = {
    ///         CELL_VIDEO_OUT_RESOLUTION_1080, //1st position, most wanted resolution - 1080p
    ///         CELL_VIDEO_OUT_RESOLUTION_720, //2nd position - 720p
    ///     };
    ///     numResolutions = 2;
    /// </code>
    /// </example>
    /// <returns>
    /// 0 will be returned if nothing given is available, otherwise
    /// the 'CellVideoOutResolutionId' ID will be returned.
    /// </returns>
    static unsigned int GetBestVideoMode(const unsigned int* resolutions, unsigned int numResolutions);

private:
    PSGLcontext* glContext = nullptr;
    PSGLdevice* glDevice = nullptr;
};
